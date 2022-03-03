//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Expression operand
 * \details
 * Class description
 * -----
 * This class defines the operand of the expression.
 * It is derived from the ExpressionSymbol class.
 * The class object provides the value of the operand.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef EXPRESSIONOPERAND_H
#define EXPRESSIONOPERAND_H

#include "expression_symbol.h"

class ExpressionOperand : public ExpressionSymbol
{
public:
    ExpressionOperand();
    ExpressionOperand(const ExpressionOperand& obj) = default;
    ExpressionOperand& operator=(const ExpressionOperand& obj) = default;
    ~ExpressionOperand() = default;
    // Functions...
    double value();

private:
    // Variables...
    double value_;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of getting the symbol value.
 * \return Symbol value.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
double ExpressionOperand::value()
{
    return value_;
}
#endif // EXPRESSIONOPERAND_H
