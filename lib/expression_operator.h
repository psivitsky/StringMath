//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Expression operator
 * \details
 * Class description
 * -----
 * This class specifies the operator of the expression.
 * It is derived from the ExpressionSymbol class.
 * The class object provides the type of the operator.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef EXPRESSIONOPERATOR_H
#define EXPRESSIONOPERATOR_H

#include "expression_symbol.h"

enum ExpressionOperatorType
{
    defaultType,
    multType,
    divType,
    sumType,
    diffType
};

class ExpressionOperator : public ExpressionSymbol
{
public:
    ExpressionOperator();
    ExpressionOperator(const ExpressionOperator& obj) = default;
    ExpressionOperator& operator=(const ExpressionOperator& obj) = default;
    ~ExpressionOperator() = default;
    // Functions...
    ExpressionOperatorType operator_type();

private:
    // Variables...
    ExpressionOperatorType operator_type_;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline ExpressionOperator::ExpressionOperator()
    : ExpressionSymbol(), operator_type_(defaultType)
{
    symbol_type_ = operandType;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of getting the type of symbol.
 * \return Symbol type.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline ExpressionOperatorType ExpressionOperator::operator_type()
{
    return operator_type_;
}
#endif // EXPRESSIONOPERATOR_H
