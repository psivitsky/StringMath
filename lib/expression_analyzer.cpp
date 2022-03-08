#include "expression_analyzer.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] precisionValue The precision of calculation result (an integer
 * non-negative value).
 * \param[in] constants The container with constants (StringMathConstant
 * objects).
 * \param[in] functions The container with functions (StringMathFunction
 * objects).
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionAnalyzer::ExpressionAnalyzer(
    int precision, const QVector<StringMathConstant>& constants,
    const QVector<StringMathFunction>& functions)
    : precision_(precision), function_(functions), constants_(constants),
      functions_(functions)
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The expression analyzer function.
 * \param[in] expressionStr The expression string to analyze.
 * \param[in] calcResultStr The calculation result.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::analyze(const QString& expressionStr,
                                 QString&       calcResultStr) const
{
    QString temp_str_1 = expressionStr;
    QString temp_str_2 = "";

    brackets_replacing(temp_str_1);

    QString                    func_name = "";
    QVector<ExpressionSymbol*> symbols;
    parsing(temp_str_1, symbols, func_name);

    QVector<ExpressionSymbol*> interpreted_symbols;
    first_rank_operators_.interpret(symbols, interpreted_symbols);

    double calc_result = second_rank_operators_.interpret(interpreted_symbols);
    calc_result = function_.interpret(calc_result, func_name);

    calcResultStr = QString::number(calc_result, 'f', precision_);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of replacing brackets.\n
 * The function finds and replaces brackets from 'opening_brackets' and
 * 'closing_brackets' with 'base_opening_bracket' and 'base_closing_bracket'.
 * \param[in,out] expressionStr The expression string with brackets to replace.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::brackets_replacing(QString& expressionStr) const
{
    foreach(QString opening_bracket, opening_brackets)
        expressionStr =
            expressionStr.replace(opening_bracket, base_opening_bracket);

    foreach(QString closing_bracket, closing_brackets)
        expressionStr =
            expressionStr.replace(closing_bracket, base_closing_bracket);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Expression parsing function.
 * \param[in] expressionStr The expression string to parse.
 * \param[out] symbols The container with expression symbols:
 * operands and operators.
 * \param[out] funcName The name of the expression function. If there
 * is no function in the expression, the name will be an empty string.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::parsing(const QString&              expressionStr,
                                 QVector<ExpressionSymbol*>& symbols,
                                 QString&                    funcName) const
{
    QString::const_iterator begin = expressionStr.begin();
    function_name_parsing(begin, expressionStr.end(), funcName);

    QString operand = "";
    while(begin != expressionStr.end())
    {
        if(operators.contains(*begin))
        {
            symbols.push_back(
                ExpressionChecker::operand_parsing(operand, constants_));
            operand = "";

            symbols.push_back(new ExpressionOperator(*begin));
            ++begin;
        }
        else if(*begin == base_opening_bracket)
        {
            subexpression_parsing(begin, expressionStr.end(), operand);

            ExpressionAnalyzer subexpression_analyzer(16, constants_,
                                                      functions_);
            subexpression_analyzer.analyze(operand, operand);
        }
        else
        {
            operand += *begin;
            ++begin;
        }
    }

    if(!operand.isEmpty())
        symbols.push_back(last_operand_parsing(operand));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function name parsing method.\n
 * The function name is at the beginning of the expression string before the
 * first bracket.
 * \param[in,out] begin The iterator pointing to the first character in the
 * parsing string.
 * \param[in] end The iterator pointing to the character after the last
 * character in the parsing string.
 * \param[out] funcName The name of the expression function.
 * If there is no function in the expression, the name will be an empty string.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::function_name_parsing(QString::const_iterator& begin,
                                               QString::const_iterator  end,
                                               QString& funcName) const
{
    funcName = "";

    QString::const_iterator opening_bracket_iterator = begin;

    int                     subsubexp_number = 0;
    QString::const_iterator iterator = begin;
    while(iterator != end)
    {
        if(operators.contains(*iterator))
        {
            if(subsubexp_number == 0)
                break;
        }
        else if(*iterator == base_opening_bracket)
        {
            if(subsubexp_number == 0)
                opening_bracket_iterator = iterator;

            ++subsubexp_number;
        }
        else if(*iterator == base_closing_bracket)
        {
            if(subsubexp_number == 1)
                break;
            else
                --subsubexp_number;
        }

        ++iterator;
    }

    if(iterator == end)
    {
        if(subsubexp_number != 0)
            throw StringMathError(
                "ExpressionAnalyzer: the closing bracket is missing!");
    }

    if(subsubexp_number == 1)
    {
        ++iterator;

        bool f_empty = true;
        while(iterator != end)
        {
            if(operators.contains(*iterator))
            {
                f_empty = false;
                break;
            }
            else if(*iterator != " ")
                throw StringMathError("ExpressionAnalyzer: an invalid symbol "
                                      "after the closing bracket!");

            ++iterator;
        }

        if(f_empty)
        {
            while(begin != opening_bracket_iterator)
            {
                funcName += *begin;
                ++begin;
            }

            ExpressionChecker::spaces_removing(funcName);
            // The function name can be empty after removing spaces!
            // However the expression contains an opening bracket.

            ++begin;
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The opening bracket skipping function.
 * \param[in,out] begin The iterator pointing to the first character in the
 * parsing string.
 * \param[in] end The iterator pointing to the character after the last
 * character in the parsing string.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::opening_bracket_skipping(
    QString::const_iterator& begin, QString::const_iterator end) const
{
    QString::const_iterator opening_bracket_iterator = begin;

    int                     subsubexp_number = 0;
    QString::const_iterator iterator = begin;
    while(iterator != end)
    {
        if(operators.contains(*iterator))
        {
            if(subsubexp_number == 0)
                break;
        }
        else if(*iterator == base_opening_bracket)
        {
            if(subsubexp_number == 0)
                opening_bracket_iterator = iterator + 1;

            ++subsubexp_number;
        }
        else if(*iterator == base_closing_bracket)
        {
            if(subsubexp_number == 1)
                break;
            else
                --subsubexp_number;
        }

        ++iterator;
    }

    if(iterator == end)
    {
        if(subsubexp_number != 0)
            throw StringMathError(
                "ExpressionAnalyzer: the closing bracket is missing!");
    }

    if(subsubexp_number == 1)
    {
        ++iterator;

        bool f_empty = true;
        while(iterator != end)
        {
            if(operators.contains(*iterator))
            {
                f_empty = false;
                break;
            }
            else if(*iterator != " ")
                throw StringMathError("ExpressionAnalyzer: an invalid symbol "
                                      "after the closing bracket!");

            ++iterator;
        }

        if(f_empty)
            begin = opening_bracket_iterator;
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The subexpression parsing function.\n
 * A subexpression is an operand that contains mathematical operations inside
 * brackets.\n
 * A subexpression may contain other subexpressions.
 * \param[in,out] begin The iterator pointing to the opening bracket of the
 * parsing string.
 * \param[in] end The iterator pointing to the character after the last
 * character in the parsing string.
 * \param[out] subExpressionStr The subexpression string.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::subexpression_parsing(QString::const_iterator& begin,
                                               QString::const_iterator  end,
                                               QString& subExpressionStr) const
{
    int subsubexp_number = 0;
    while(begin != end)
    {
        if(*begin == base_opening_bracket)
            ++subsubexp_number;
        else if(*begin == base_closing_bracket)
        {
            if(subsubexp_number == 1)
            {
                subExpressionStr += *begin;
                ++begin;

                while(begin != end)
                {
                    if(operators.contains(*begin) ||
                       (*begin == base_closing_bracket))
                        break;
                    else if(*begin != " ")
                        throw StringMathError(
                            "ExpressionAnalyzer: an invalid symbol after the "
                            "closing bracket!");

                    subExpressionStr += *begin;
                    ++begin;
                }

                return;
            }
            else
                --subsubexp_number;
        }

        subExpressionStr += *begin;
        ++begin;
    }

    if(begin == end)
        throw StringMathError(
            "ExpressionAnalyzer: the closing bracket is missing!");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The last operand parsing function.\n
 * If this operand string contains a closing bracket, it will be removed from
 * the string.
 * \param[in] operandStr The last operand string to parse.
 * \return The expression last operand symbol.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionOperand*
ExpressionAnalyzer::last_operand_parsing(QString& operandStr) const
{
    if(operandStr.contains(base_closing_bracket))
    {
        QString                 operand_without_bracket = "";
        QString::const_iterator operand_begin = operandStr.begin();
        while(operand_begin != operandStr.end())
        {
            if(*operand_begin == base_closing_bracket)
                break;

            operand_without_bracket += *operand_begin;
            ++operand_begin;
        }

        if(operand_begin == operandStr.end())
            throw StringMathError(
                "ExpressionAnalyzer: the closing bracket is missing!");

        operandStr = operand_without_bracket;
    }

    return ExpressionChecker::operand_parsing(operandStr, constants_);
}
