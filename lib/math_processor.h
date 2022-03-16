#ifndef MATHPROCESSOR_H
#define MATHPROCESSOR_H

#include "expression.h"

#include "fr_op_interpreter.h"
#include "func_interpreter.h"
#include "sr_op_interpreter.h"

namespace MathProcessor
{
double expression_calculation(const Expression*                  expression,
                              const QVector<StringMathFunction>& functions);
};
#endif // MATHPROCESSOR_H
