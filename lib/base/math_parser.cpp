#include "math_parser.h"

ExpressionOperand* operand_parsing(const QString&,
                                   const QVector<StringMathConstant>&);

Expression* subexpression_parsing(QString::const_iterator&,
                                  QString::const_iterator,
                                  QString&,
                                  const QVector<StringMathConstant>&);

void spaces_removing(QString&);

void subexpression_closure_checking(QString::const_iterator&,
                                    QString::const_iterator);

//----------------------------------------------------------------------------------
/*!
 * Expression parsing function.
 * \param[in] str The expression string to parse.
 * \param[in] constants The container with constants.
 * \param[out] expression The parsed expression.
 */
//----------------------------------------------------------------------------------
void MathParser::expression_parsing(
    const QString&                     expressionStr,
    const QVector<StringMathConstant>& constants,
    Expression&                        expression)
{
    if(!expression.symbols().isEmpty())
        throw StringMathError("MathParser: the expression is not empty!");

    QString                 operand = "";
    QString::const_iterator begin = expressionStr.begin();
    QString::const_iterator end = expressionStr.end();

    while(true)
    {
        if(begin == end)
        {
            expression.add(operand_parsing(operand, constants));
            operand = "";
            break;
        }

        if(operators.contains(*begin))
        {
            expression.add(operand_parsing(operand, constants));
            operand = "";

            expression.add(new ExpressionOperator(*begin));
        }
        else if(opening_brackets.contains(*begin))
        {
            expression.add(
                subexpression_parsing(begin, end, operand, constants));
            operand = "";

            if(begin != end)
                expression.add(new ExpressionOperator(*begin));
            else
                break;
        }
        else
            operand += *begin;

        ++begin;
    }
}
//----------------------------------------------------------------------------------
/*!
 * Operand parsing function.\n
 * The function removes spaces from the operand string, checks its syntax, and
 * replaces the constant if necessary.
 * \param[in] operandStr The operand string to parse.
 * \param[in] constants The container with constants.
 * \return A pointer to the expression operand.
 */
//----------------------------------------------------------------------------------
ExpressionOperand* operand_parsing(const QString& operandStr,
                                   const QVector<StringMathConstant>& constants)
{
    double  new_operand_val = 0.;
    QString new_operand_str = operandStr;
    spaces_removing(new_operand_str);

    if(new_operand_str.isEmpty())
        return new ExpressionOperand();

    QRegExp checker("^(-)?\\d+(\\.\\d*)?$");
    if(checker.exactMatch(new_operand_str))
        new_operand_val = new_operand_str.toDouble();
    else
    {
        bool f_constant_replaced = false;
        foreach(StringMathConstant constant, constants)
        {
            if(constant.name() == new_operand_str)
            {
                new_operand_val = constant.value();
                f_constant_replaced = true;
                break;
            }
        }

        if(!f_constant_replaced)
            throw StringMathError("MathParser: the operand \"" +
                                  new_operand_str.toStdString() +
                                  "\" is invalid!");
    }

    return new ExpressionOperand(new_operand_val);
}
//----------------------------------------------------------------------------------
/*!
 * Subexpression parsing function.\n
 * A subexpression is an operand that contains mathematical operations inside
 * brackets. The subexpression may contain other subexpressions.
 * \param[in,out] begin The iterator pointing to the opening bracket in the
 * parsing string. After parsing, the iterator points to the next operator or
 * the end of the expression string.
 * \param[in] end The iterator pointing to the character after the last
 * character in the parsing string.
 * \param[in] funcName Raw function name.
 * \param[in] constants The container with constants.
 * \return A pointer to the parsed subexpression.
 */
//----------------------------------------------------------------------------------
Expression* subexpression_parsing(QString::const_iterator&           begin,
                                  QString::const_iterator            end,
                                  QString&                           funcName,
                                  const QVector<StringMathConstant>& constants)
{
    Expression* expression = new Expression();

    spaces_removing(funcName);
    expression->set_function_name(funcName);

    ++begin;

    QString operand = "";
    while(true)
    {
        if(begin == end)
        {
            delete expression;
            throw StringMathError(
                "MathParser: the closing bracket is missing!");
        }

        if(MathParser::operators.contains(*begin))
        {
            expression->add(operand_parsing(operand, constants));
            operand = "";

            expression->add(new ExpressionOperator(*begin));
        }
        else if(MathParser::opening_brackets.contains(*begin))
        {
            expression->add(
                subexpression_parsing(begin, end, operand, constants));
            operand = "";

            if(begin == end)
            {
                delete expression;
                throw StringMathError(
                    "MathParser: the closing bracket is missing!");
            }

            if(MathParser::closing_brackets.contains(*begin))
            {
                subexpression_closure_checking(begin, end);
                break;
            }

            expression->add(new ExpressionOperator(*begin));
        }
        else if(MathParser::closing_brackets.contains(*begin))
        {
            expression->add(operand_parsing(operand, constants));

            subexpression_closure_checking(begin, end);
            break;
        }
        else
            operand += *begin;

        ++begin;
    }

    return expression;
}
//----------------------------------------------------------------------------------
/*!
 * Spaces removing function.
 * \param[in,out] str The input string with spaces and
 * the output string without spaces.
 */
//----------------------------------------------------------------------------------
void spaces_removing(QString& str)
{
    while(true)
    {
        if(str.isEmpty())
            break;

        if(str.at(0) == " ")
            str.remove(0, 1);
        else if(str.at(0) == "\t")
            str.remove(0, 1);
        else if(str.at(str.length() - 1) == " ")
            str.remove(str.length() - 1, 1);
        else if(str.at(str.length() - 1) == "\t")
            str.remove(str.length() - 1, 1);
        else
            break;
    }
}
//----------------------------------------------------------------------------------
/*!
 * The function of checking the closure of the subexpression.\n
 * After the subexpression, there must be a closing bracket of the parent
 * subexpression, an operator, or the end of the expression string.
 * \param[in,out] begin The iterator pointing to the closing bracket in the
 * parsing string.
 * \param[in] end The iterator pointing to the character after the last
 * character in the parsing string.
 */
//----------------------------------------------------------------------------------
void subexpression_closure_checking(QString::const_iterator& begin,
                                    QString::const_iterator  end)
{
    ++begin;

    while((*begin == " ") && (begin != end))
        ++begin;

    if(!MathParser::closing_brackets.contains(*begin) &&
       !MathParser::operators.contains(*begin) && (begin != end))
        throw StringMathError("MathParser: there should be an operator or a "
                              "closing bracket after the subexpression!");
}
