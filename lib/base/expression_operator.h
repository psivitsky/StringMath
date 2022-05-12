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
    sumType,
    diffType,
    multType,
    divType,
    powType
};

enum ExpressionOperatorRank
{
    defaultRank,
    hyper1,
    hyper2,
    hyper3
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
    void                   set_operator(const QChar& character);
    ExpressionOperatorType operator_type() const;
    ExpressionOperatorRank operator_rank() const;

private:
    // Variables...
    ExpressionOperatorType operator_type_;
    ExpressionOperatorRank operator_rank_;
};
#endif // EXPRESSIONOPERATOR_H
