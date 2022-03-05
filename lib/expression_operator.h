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

#include <QChar>

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
    ExpressionOperator(const QChar& character);
    ExpressionOperator(const ExpressionOperator& obj) = default;
    ExpressionOperator& operator=(const ExpressionOperator& obj) = default;
    ~ExpressionOperator() = default;
    // Functions...
    void set_operator_type(ExpressionOperatorType operatorType);
    ExpressionOperatorType operator_type() const;

private:
    // Variables...
    ExpressionOperatorType operator_type_;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The default constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline ExpressionOperator::ExpressionOperator()
    : ExpressionSymbol(), operator_type_(defaultType)
{
    symbol_type_ = operatorType;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] character Operator character.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline ExpressionOperator::ExpressionOperator(const QChar& character)
    : ExpressionSymbol(), operator_type_(defaultType)
{
    symbol_type_ = operatorType;

    if(character == '*')
        operator_type_ = multType;
    else if(character == '/')
        operator_type_ = divType;
    else if(character == '+')
        operator_type_ = sumType;
    else if(character == '-')
        operator_type_ = diffType;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of setting the operator type.
 * \param[in] operatorType Operator type.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline void
ExpressionOperator::set_operator_type(ExpressionOperatorType operatorType)
{
    operator_type_ = operatorType;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of getting the operator type.
 * \return Operator type.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline ExpressionOperatorType ExpressionOperator::operator_type() const
{
    return operator_type_;
}
#endif // EXPRESSIONOPERATOR_H
