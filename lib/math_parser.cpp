#include "math_parser.h"

Expression* subexpression_parsing(QString::const_iterator&,
                                  QString::const_iterator,
                                  const QVector<StringMathConstant>&);

bool closing_bracket_checking(QString::const_iterator&,
                              QString::const_iterator);

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Expression parsing function.
 * \param[in] str The expression string to parse.
 * \param[in] constants The container with constants.
 * \return A pointer to the parsed expression.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
Expression*
MathParser::expression_parsing(const QString&                     str,
                               const QVector<StringMathConstant>& constants)
{
    Expression expression;

    QString::const_iterator begin = str.begin();

    QString operand = "";
    while(true)
    {
        if(operators.contains(*begin) || begin == str.end())
        {
            expression.add(MathChecker::operand_parsing(operand, constants));
            operand = "";

            if(begin != str.end())
                expression.add(new ExpressionOperator(*begin));
            else
                break;
        }
        else if(opening_brackets.contains(*begin))
        {
            ++begin;

            Expression* subexpression =
                subexpression_parsing(begin, str.end(), constants);

            MathChecker::spaces_removing(operand);
            subexpression->set_function_name(operand);
            operand = "";

            expression.add(subexpression);

            if(begin != str.end())
                expression.add(new ExpressionOperator(*begin));
            else
                break;
        }
        else
            operand += *begin;

        ++begin;
    }

    return new Expression(expression);
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
 * \param[in] constants The container with constants.
 * \return The subexpression string.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
Expression* subexpression_parsing(QString::const_iterator&           begin,
                                  QString::const_iterator            end,
                                  const QVector<StringMathConstant>& constants)
{
    Expression expression;

    bool    f_closed = false;
    QString operand = "";
    while(true)
    {
        if(MathParser::operators.contains(*begin) || begin == end)
        {
            expression.add(MathChecker::operand_parsing(operand, constants));
            operand = "";

            if(begin == end)
                break;
            else
                expression.add(new ExpressionOperator(*begin));
        }
        else if(MathParser::opening_brackets.contains(*begin))
        {
            ++begin;

            Expression* subexpression =
                subexpression_parsing(begin, end, constants);

            MathChecker::spaces_removing(operand);
            subexpression->set_function_name(operand);
            operand = "";

            expression.add(subexpression);

            if(begin == end)
                break;
            else if(MathParser::closing_brackets.contains(*begin))
            {
                f_closed = true;

                if(closing_bracket_checking(begin, end))
                    break;
                else
                    throw StringMathError(
                        "ExpressionAnalyzer: there should be an operator or a "
                        "closing bracket after the subexpression!");
            }
            else
                expression.add(new ExpressionOperator(*begin));
        }
        else if(MathParser::closing_brackets.contains(*begin))
        {
            expression.add(MathChecker::operand_parsing(operand, constants));

            f_closed = true;

            if(closing_bracket_checking(begin, end))
                break;
            else
                throw StringMathError(
                    "ExpressionAnalyzer: there should be an operator or a "
                    "closing bracket after the subexpression!");
        }
        else
            operand += *begin;

        ++begin;
    }

    if(!f_closed)
        throw StringMathError(
            "ExpressionAnalyzer: the closing bracket is missing!");

    return new Expression(expression);
}

bool closing_bracket_checking(QString::const_iterator& begin,
                              QString::const_iterator  end)
{
    ++begin;

    while((*begin == " ") && (begin != end))
        ++begin;

    if(MathParser::closing_brackets.contains(*begin) ||
       MathParser::operators.contains(*begin) || (begin == end))
        return true;

    return false;
}
