#ifndef MATHPROCESSOR_H
#define MATHPROCESSOR_H

#include "expression.h"
#include "expression_operand.h"
#include "expression_operator.h"

#include "string_math_function.h"

//----------------------------------------------------------------------------------
//! \details Namespace with expressions processing functionality.
//----------------------------------------------------------------------------------
namespace MathProcessor
{
const QVector<ExpressionOperatorType> hyper_1_operators = {sumType, diffType};
const QVector<ExpressionOperatorType> hyper_2_operators = {multType, divType};

double expression_calculation(const Expression&                  expression,
                              const QVector<StringMathFunction>& functions);
}; // namespace MathProcessor

#endif // MATHPROCESSOR_H
