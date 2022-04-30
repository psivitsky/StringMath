//----------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------
#ifndef EXPRESSIONOPERATOR_H
#define EXPRESSIONOPERATOR_H

#include "expression_symbol.h"

#include <QChar>

enum ExpressionOperatorType
{
    defaultType,
    powType,
    multType,
    divType,
    sumType,
    diffType
};

class ExpressionOperator : public ExpressionSymbol
{
public:
    ExpressionOperator();
    explicit ExpressionOperator(const QChar& character);
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
#endif // EXPRESSIONOPERATOR_H
