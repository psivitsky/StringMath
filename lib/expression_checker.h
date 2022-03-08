#ifndef EXPRESSIONOPERANDCHECKER_H
#define EXPRESSIONOPERANDCHECKER_H

#include "expression_operand.h"
#include "expression_operator.h"
#include "string_math_base.h"

#include <QVector>

namespace ExpressionChecker
{
ExpressionOperand*
operand_checker(QVector<ExpressionSymbol*>::const_iterator begin,
                QVector<ExpressionSymbol*>::const_iterator end);
ExpressionOperator*
operator_checker(QVector<ExpressionSymbol*>::const_iterator begin,
                 QVector<ExpressionSymbol*>::const_iterator end);
};     // namespace ExpressionChecker
#endif // EXPRESSIONOPERANDCHECKER_H
