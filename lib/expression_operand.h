#ifndef EXPRESSIONOPERAND_H
#define EXPRESSIONOPERAND_H

#include "expression_symbol.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Expression operand
 * \details
 * Class description
 * -----
 * This class specifies the operand of the expression.
 * It is derived from the ExpressionSymbol class.
 * The class object provides the value of the operand.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
class ExpressionOperand : public ExpressionSymbol
{
public:
    ExpressionOperand();
    ExpressionOperand(const ExpressionOperand& obj) = default;
    ExpressionOperand& operator=(const ExpressionOperand& obj) = default;
    ~ExpressionOperand() = default;
    // Functions...
    bool is_empty() const;

    void   set_value(double operandValue);
    double value() const;

private:
    // Variables...
    bool   f_empty;
    double value_;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline ExpressionOperand::ExpressionOperand()
    : ExpressionSymbol(), f_empty(true), value_(0.)
{
    symbol_type_ = operandType;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of checking, whether the operand is empty.
 * \return The result of the check:
 * true - the operand is empty,
 * false - the operand is not empty.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline bool ExpressionOperand::is_empty() const
{
    return f_empty;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of setting the operand value.\n
 * After setting the value, the operand is no longer empty.
 * \param[in] operandValue Operand value.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline void ExpressionOperand::set_value(double operandValue)
{
    f_empty = false;
    value_ = operandValue;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of getting the operand value.
 * \return Operand value.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline double ExpressionOperand::value() const
{
    return value_;
}
#endif // EXPRESSIONOPERAND_H
