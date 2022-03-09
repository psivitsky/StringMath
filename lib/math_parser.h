//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Mathematical expression parser
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef MATHPARSER_H
#define MATHPARSER_H

#include <QStringList>

#include "expression.h"

#include "math_checker.h"

namespace MathParser
{
const QStringList opening_brackets = {"(", "[", "{"};
const QStringList closing_brackets = {")", "]", "}"};

const QStringList operators = {"*", "/", "+", "-"};

Expression* expression_parsing(const QString&                     str,
                               const QVector<StringMathConstant>& constants);
} // namespace MathParser
#endif // MATHPARSER_H
