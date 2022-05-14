#include "expression_operand.h"
//----------------------------------------------------------------------------------
//! \details The default constructor.
//----------------------------------------------------------------------------------
ExpressionOperand::ExpressionOperand() : f_empty(true), value_(0.)
{
    symbol_type_ = operandType;
}
//----------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] operandValue Operand value.
 */
//----------------------------------------------------------------------------------
ExpressionOperand::ExpressionOperand(double operandValue)
    : f_empty(false), value_(operandValue)
{
    symbol_type_ = operandType;
}
//----------------------------------------------------------------------------------
/*!
 * The function of checking, whether the operand is empty.
 * \return The result of the check:
 * true - the operand is empty,
 * false - the operand is not empty.
 */
//----------------------------------------------------------------------------------
bool ExpressionOperand::is_empty() const
{
    return f_empty;
}
//----------------------------------------------------------------------------------
/*!
 * The function of setting the operand value.\n
 * After setting the value, the operand is no longer empty.
 * \param[in] operandValue Operand value.
 */
//----------------------------------------------------------------------------------
void ExpressionOperand::set_value(double operandValue)
{
    f_empty = false;
    value_ = operandValue;
}
//----------------------------------------------------------------------------------
/*!
 * The function of getting the operand value.
 * \return Operand value.
 */
//----------------------------------------------------------------------------------
double ExpressionOperand::value() const
{
    return value_;
}
