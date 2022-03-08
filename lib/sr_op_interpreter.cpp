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
    ExpressionOperand*  operand =
        ExpressionChecker::operand_checking(iterator, symbols.end());
    ++iterator;

    if(operand->is_empty())
        operand->set_value(0.);

    double calc_result = operand->value();

    while(iterator != symbols.end())
    {
        expression_operator =
            ExpressionChecker::operator_checking(iterator, symbols.end());
        ++iterator;
        operand = ExpressionChecker::operand_checking(iterator, symbols.end());
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
