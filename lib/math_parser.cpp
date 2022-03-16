#include "math_parser.h"

Expression* subexpression_parsing(QString::const_iterator&,
                                  QString::const_iterator, QString&,
                                  const QVector<StringMathConstant>&);

void subexpression_closure_checking(QString::const_iterator&,
                                    QString::const_iterator);

//----------------------------------------------------------------------------------
/*!
 * Expression parsing function.
 * \param[in] str The expression string to parse.
 * \param[in] constants The container with constants.
 * \return A pointer to the parsed expression.
 */
//----------------------------------------------------------------------------------
Expression*
MathParser::expression_parsing(const QString&                     str,
                               const QVector<StringMathConstant>& constants)
{
    Expression expression;

    QString::const_iterator begin = str.begin();

    QString operand = "";
    while(true)
    {
        if(begin == str.end())
        {
            expression.add(MathChecker::operand_parsing(operand, constants));
            operand = "";
            break;
        }
        else if(operators.contains(*begin))
        {
            expression.add(MathChecker::operand_parsing(operand, constants));
            operand = "";

            expression.add(new ExpressionOperator(*begin));
        }
        else if(opening_brackets.contains(*begin))
        {
            expression.add(
                subexpression_parsing(begin, str.end(), operand, constants));
            operand = "";

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
    Expression expression;

    MathChecker::spaces_removing(funcName);
    expression.set_function_name(funcName);

    ++begin;

    QString operand = "";
    while(true)
    {
        if(begin == end)
            throw StringMathError(
                "ExpressionAnalyzer: the closing bracket is missing!");
        else if(MathParser::operators.contains(*begin))
        {
            expression.add(MathChecker::operand_parsing(operand, constants));
            operand = "";

            expression.add(new ExpressionOperator(*begin));
        }
        else if(MathParser::opening_brackets.contains(*begin))
        {
            expression.add(
                subexpression_parsing(begin, end, operand, constants));
            operand = "";

            if(begin == end)
                throw StringMathError(
                    "ExpressionAnalyzer: the closing bracket is missing!");
            else if(MathParser::closing_brackets.contains(*begin))
            {
                subexpression_closure_checking(begin, end);
                break;
            }
            else
                expression.add(new ExpressionOperator(*begin));
        }
        else if(MathParser::closing_brackets.contains(*begin))
        {
            expression.add(MathChecker::operand_parsing(operand, constants));

            subexpression_closure_checking(begin, end);
            break;
        }
        else
            operand += *begin;

        ++begin;
    }

    return new Expression(expression);
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
        throw StringMathError(
            "ExpressionAnalyzer: there should be an operator or a "
            "closing bracket after the subexpression!");
}
