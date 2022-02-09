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
 * Second rang operators interpreter function.
 * \param[in] expressionStr The expression string to interpret.
 * \param[out] interpretedExpStr The interpreted expression string.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void SROpInterpreter::interpret(const QString &expressionStr, QString &interpretedExpStr) const
{
    //The expression location - # cos(1+1) -> 1+1.

    double result = calculate(expressionStr.begin(), interpretedExpStr.end());

    //The string result former - # "cos(" + "2" + ")".
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Second rang operators calculation function.
 * \param[in] begin The expression string begin.
 * \param[in] end The expression string end.
 * \return The calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double SROpInterpreter::calculate(QString::const_iterator begin, QString::const_iterator end) const
{
    //The left operand location - # 1+1 -> 1.
    double  left_operand = 0.;
    ++begin;

    //In case of expression last operand...
    if(begin == end)
        return left_operand;

    //The operator definer - # 1+1 -> +.
    QString math_operator = "";
    ++begin;

    if(math_operator == "+")
        left_operand += calculate(begin, end);
    else if(math_operator == "-")
        left_operand -= calculate(begin, end);

    return left_operand;
}
