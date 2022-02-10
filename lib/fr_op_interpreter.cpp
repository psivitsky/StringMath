#include "fr_op_interpreter.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] constants The container with constants (StringMathConstant objects).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
FROpInterpreter::FROpInterpreter(const QVector<StringMathConstant> &constants) : OpInterpreter(constants)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * First rank operators interpreter function.
 * \param[in] expressionStr The expression string to interpret.
 * \param[out] interpretedExpStr The interpreted expression string.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FROpInterpreter::interpret(const QString &expressionStr, QString &interpretedExpStr) const
{
    interpretedExpStr = "";    

    QString::const_iterator index = expressionStr.begin();
    if(expressionStr.contains(opening_bracket))
    {
        while(*index != opening_bracket)
            ++index;
        ++index;
    }

    QString operand = "";
    while(true)
    {
        if(index == expressionStr.end())
        {
            interpretedExpStr += operand;
            break;
        }
        else
        {
            if(second_rank_operators.contains(*index))
            {
                interpretedExpStr += operand;
                operand = "";
                interpretedExpStr += *index;
                ++index;
            }
            else if(first_rank_operators.contains(*index))
                calculate(index, expressionStr.end(), operand);
            else
            {
                operand += *index;
                ++index;
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The first rank operator calculation function.\n
 * At the end of processing, the "begin" iterator points to the next operator, the closing bracket or the end of the string.\n
 * The calculation result will be used as the left operand for the next operation.
 * \param[in,out] begin The iterator pointing to the first character in the processing string.
 * \param[in] end The iterator pointing to the character after the last character in the processing string.
 * \param[in,out] leftOperand The left operand of the operator and the result of the calculation.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FROpInterpreter::calculate(QString::const_iterator &begin, QString::const_iterator end, QString &leftOperand) const
{
    QString first_rank_operator = *begin;
    ++begin;

    QString right_operand = "";
    while(begin != end)
    {
        if(first_rank_operators.contains(*begin))
            break;
        else if(second_rank_operators.contains(*begin))
            break;
        else if(*begin == closing_bracket)
            break;
        else
            right_operand += *begin;
        ++begin;
    }

    operand_processing(leftOperand);
    operand_processing(right_operand);

    QString calculation_result = "";
    if(first_rank_operator == mult_operator)
        calculation_result = QString::number(leftOperand.toDouble() * right_operand.toDouble(), 'f', precision);
    else
        calculation_result = QString::number(leftOperand.toDouble() / right_operand.toDouble(), 'f', precision);

    leftOperand = calculation_result;
}
