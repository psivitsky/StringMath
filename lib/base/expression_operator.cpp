#include "expression_operator.h"
//----------------------------------------------------------------------------------
//! \details The default constructor.
//----------------------------------------------------------------------------------
ExpressionOperator::ExpressionOperator()
    : operator_type_(defaultType), operator_rank_(defaultRank)
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
    : operator_type_(defaultType), operator_rank_(defaultRank)
{
    symbol_type_ = operatorType;

    set_operator(character);
}
//----------------------------------------------------------------------------------
/*!
 * The function of setting the operator.
 * \param[in] character Operator character.
 */
//----------------------------------------------------------------------------------
void ExpressionOperator::set_operator(const QChar& character)
{
    if(character == '+')
    {
        operator_type_ = sumType;
        operator_rank_ = hyper1;
    }
    else if(character == '-')
    {
        operator_type_ = diffType;
        operator_rank_ = hyper1;
    }
    else if(character == '*')
    {
        operator_type_ = multType;
        operator_rank_ = hyper2;
    }
    else if(character == '/')
    {
        operator_type_ = divType;
        operator_rank_ = hyper2;
    }
    else if(character == '^')
    {
        operator_type_ = powType;
        operator_rank_ = hyper3;
    }
    else
    {
        operator_type_ = defaultType;
        operator_rank_ = defaultRank;
    }
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
//----------------------------------------------------------------------------------
/*!
 * The function of getting the operator rank.
 * \return Operator rank.
 */
//----------------------------------------------------------------------------------
ExpressionOperatorRank ExpressionOperator::operator_rank() const
{
    return operator_rank_;
}
