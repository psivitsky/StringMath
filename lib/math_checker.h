#ifndef MATHCHECKER_H
#define MATHCHECKER_H

#include "string_math_constant.h"

#include "expression_operand.h"
#include "expression_operator.h"

#include <QRegExp>
#include <QVector>

namespace MathChecker
{
ExpressionOperand*
operand_parsing(const QString&                     operandStr,
                const QVector<StringMathConstant>& constants);

void spaces_removing(QString& str);

ExpressionOperand*
operand_checking(QVector<ExpressionSymbol*>::const_iterator begin,
                 QVector<ExpressionSymbol*>::const_iterator end);

ExpressionOperator*
operator_checking(QVector<ExpressionSymbol*>::const_iterator begin,
                  QVector<ExpressionSymbol*>::const_iterator end);
};     // namespace MathChecker
#endif // MATHCHECKER_H