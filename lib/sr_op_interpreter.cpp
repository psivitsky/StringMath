#include "sr_op_interpreter.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] constants The container with constants (StringMathConstant objects).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
SROpInterpreter::SROpInterpreter(const QVector<StringMathConstant> &constants) : OpInterpreter(constants)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Second rank operators interpreter function.
 * \param[in] expressionStr The expression string to interpret.
 * \param[out] interpretedExpStr The interpreted expression string.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void SROpInterpreter::interpret(const QString &expressionStr, QString &interpretedExpStr) const
{
    interpretedExpStr = "";

    QString::const_iterator begin = expressionStr.begin();
    if(expressionStr.contains(opening_bracket))
        opening_bracket_skipping(begin, expressionStr.end(), interpretedExpStr);

    double result = calculate(begin, expressionStr.end(), true);

    interpretedExpStr += QString::number(result, 'f', precision);
    if(expressionStr.contains(closing_bracket))
        interpretedExpStr += closing_bracket;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The second rank operators calculation function.\n
 * If the function finds the second rank operator, it calculates the sum or difference of the current operand and the rest of the expression.\n
 * If the first operation is a difference and the first operand is empty, it will be replaced with zero.\n
 * If the operand is the last one and there is no operator, then the function returns the value of the last operand.
 * \param[in] begin The iterator pointing to the first character in the processing string.
 * \param[in] end The iterator pointing to the character after the last character in the processing string.
 * \param[in] fFirstOperand The first operand flag: true - the operand is the first in the expression, false - otherwise.
 * \return The calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double SROpInterpreter::calculate(QString::const_iterator begin, QString::const_iterator end, bool fFirstOperand) const
{
    QString operand = "";
    while((begin != end) && (*begin != closing_bracket))
    {
        if(*begin == sum_operator)
        {
            ++begin;
            operand_processing(operand);
            return operand.toDouble() + calculate(begin, end, false);
        }
        else if(*begin == diff_operator)
        {
            ++begin;

            if(fFirstOperand)
            {
                spaces_removing(operand);
                if(operand.isEmpty())
                    operand = "0";
            }

            operand_processing(operand);
            return operand.toDouble() - calculate(begin, end, false);
        }
        else
        {
            operand += *begin;
            ++begin;
        }
    }

    operand_processing(operand);
    return operand.toDouble();
}
