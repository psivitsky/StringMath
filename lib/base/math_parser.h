#ifndef MATHPARSER_H
#define MATHPARSER_H

#include <QStringList>

#include "expression.h"
#include "expression_operand.h"
#include "expression_operator.h"

#include "string_math_constant.h"

//----------------------------------------------------------------------------------
//! \details Namespace with expression parsing functionality.
//----------------------------------------------------------------------------------
namespace MathParser
{
const QStringList opening_brackets = {"(", "[", "{"};
const QStringList closing_brackets = {")", "]", "}"};

const QStringList operators = {"^", "*", "/", "+", "-"};

void expression_parsing(const QString&                     expressionStr,
                        const QVector<StringMathConstant>& constants,
                        Expression&                        expression);
} // namespace MathParser

#endif // MATHPARSER_H
