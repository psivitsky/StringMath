#include "expression_operator.h"
//----------------------------------------------------------------------------------
//! \details The default constructor.
//----------------------------------------------------------------------------------
ExpressionOperator::ExpressionOperator()
    : ExpressionSymbol(), operator_type_(defaultType)
{
    symbol_type_ = operatorType;
}
//----------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] character Operator character.
 */
//----------------------------------------------------------------------------------
ExpressionOperator::ExpressionOperator(const QChar& character)
    : ExpressionSymbol(), operator_type_(defaultType)
{
    symbol_type_ = operatorType;

    if(character == '^')
        operator_type_ = powType;
    else if(character == '*')
        operator_type_ = multType;
    else if(character == '/')
        operator_type_ = divType;
    else if(character == '+')
        operator_type_ = sumType;
    else if(character == '-')
        operator_type_ = diffType;
}
//----------------------------------------------------------------------------------
/*!
 * The function of setting the operator type.
 * \param[in] operatorType Operator type.
 */
//----------------------------------------------------------------------------------
void ExpressionOperator::set_operator_type(ExpressionOperatorType operatorType)
{
    operator_type_ = operatorType;
}
//----------------------------------------------------------------------------------
/*!
 * The function of getting the operator type.
 * \return Operator type.
 */
//----------------------------------------------------------------------------------
ExpressionOperatorType ExpressionOperator::operator_type() const
{
    return operator_type_;
}
