#ifndef MATHPROCESSOR_H
#define MATHPROCESSOR_H

#include "expression.h"

#include "math_checker.h"

#include "func_interpreter.h"

namespace MathProcessor
{
const QVector<ExpressionOperatorType> hyper_1_operators = {sumType, diffType};
const QVector<ExpressionOperatorType> hyper_2_operators = {multType, divType};

double expression_calculation(const Expression*                  expression,
                              const QVector<StringMathFunction>& functions);
};     // namespace MathProcessor
#endif // MATHPROCESSOR_H
