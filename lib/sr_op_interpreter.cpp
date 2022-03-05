#include "sr_op_interpreter.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
SROpInterpreter::SROpInterpreter()
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Second rank operators interpreter function.
 * \param[in] symbols Expression symbols to interpret.
 * \return The calculation result.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
double
SROpInterpreter::interpret(const QVector<ExpressionSymbol*>& symbols) const
{
    QVector<ExpressionSymbol*>::const_iterator iterator = symbols.begin();

    ExpressionOperator* expression_operator = nullptr;
    ExpressionOperand*  operand = operand_checker(iterator, symbols.end());
    ++iterator;

    if(operand->is_empty())
        operand->set_value(0.);

    double calc_result = operand->value();

    while(iterator != symbols.end())
    {
        expression_operator = operator_checker(iterator, symbols.end());
        ++iterator;
        operand = operand_checker(iterator, symbols.end());
        ++iterator;

        if(expression_operator->operator_type() == sumType)
            calc_result += operand->value();
        else if(expression_operator->operator_type() == diffType)
            calc_result -= operand->value();
        else
            throw StringMathError(
                "SROpInterpreter: there is no such second rank operator!");
    }

    return calc_result;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Operator checker function.
 * \param[in] begin The iterator pointing to the operator in the parsing
 * container.
 * \param[in] end The iterator pointing to a symbol after the last
 * symbol in the parsing container.
 * \return centerOperator Pointer to the operator.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionOperator* SROpInterpreter::operator_checker(
    QVector<ExpressionSymbol*>::const_iterator begin,
    QVector<ExpressionSymbol*>::const_iterator end) const
{
    if(begin == end)
        throw StringMathError("SROpInterpreter: the expression syntax error!");

    ExpressionOperator* expression_operator = 0;

    if((*begin)->symbol_type() == operatorType)
        expression_operator = dynamic_cast<ExpressionOperator*>(*begin);
    else
        throw StringMathError("SROpInterpreter: the expression syntax error!");

    return expression_operator;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Operand checker function.
 * \param[in] begin The iterator pointing to the operand in the parsing
 * container.
 * \param[in] end The iterator pointing to a symbol after the last
 * symbol in the parsing container.
 * \return Pointer to the operand.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionOperand* SROpInterpreter::operand_checker(
    QVector<ExpressionSymbol*>::const_iterator begin,
    QVector<ExpressionSymbol*>::const_iterator end) const
{
    if(begin == end)
        throw StringMathError("SROpInterpreter: the expression syntax error!");

    ExpressionOperand* operand = 0;

    if((*begin)->symbol_type() == operandType)
        operand = dynamic_cast<ExpressionOperand*>(*begin);
    else
        throw StringMathError("SROpInterpreter: the expression syntax error!");

    return operand;
}
