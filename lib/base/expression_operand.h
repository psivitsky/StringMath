#ifndef EXPRESSIONOPERAND_H
#define EXPRESSIONOPERAND_H

#include "expression_symbol.h"

//----------------------------------------------------------------------------------
/*!
 * \brief
 * Expression operand
 * \details
 * Class description
 * -----
 * This class specifies the operand of the expression.
 * It is derived from the ExpressionSymbol class.
 * The class object provides the value of the operand.
 * If the value is not set, the operand is considered empty.
 */
//----------------------------------------------------------------------------------
class ExpressionOperand : public ExpressionSymbol
{
public:
    ExpressionOperand();
    explicit ExpressionOperand(double operandValue);
    ExpressionOperand(const ExpressionOperand& obj) = default;
    ExpressionOperand& operator=(const ExpressionOperand& obj) = default;
    virtual ~ExpressionOperand() = default;
    // Functions...
    bool is_empty() const;

    void   set_value(double operandValue);
    double value() const;

protected:
    // Variables...
    bool   f_empty;
    double value_;
};
#endif // EXPRESSIONOPERAND_H
