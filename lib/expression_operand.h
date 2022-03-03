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
    void   set_value(double operandValue);
    double value() const;

private:
    // Variables...
    double value_;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline ExpressionOperand::ExpressionOperand() : ExpressionSymbol(), value_(0.)
{
    symbol_type_ = operandType;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of setting the operand value.
 * \param[in] operandValue Operand value.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline void ExpressionOperand::set_value(double operandValue)
{
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

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Expression empty operand
 * \details
 * Class description
 * -----
 * This class specifies an empty operand of the expression.
 * It is derived from the ExpressionSymbol class.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
class ExpressionEmptyOperand : public ExpressionSymbol
{
public:
    ExpressionEmptyOperand();
    ExpressionEmptyOperand(const ExpressionEmptyOperand& obj) = default;
    ExpressionEmptyOperand&
    operator=(const ExpressionEmptyOperand& obj) = default;
    ~ExpressionEmptyOperand() = default;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline ExpressionEmptyOperand::ExpressionEmptyOperand() : ExpressionSymbol()
{
    symbol_type_ = emptyOperandType;
}
#endif // EXPRESSIONOPERAND_H