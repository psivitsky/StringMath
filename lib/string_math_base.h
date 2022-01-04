#ifndef STRING_MATH_BASE_H
#define STRING_MATH_BASE_H

#include    <QStringList>

namespace StringMathBase
{
    static const int    mid_prec = 16;      //!< \details The precision of intermediate calculations.

    static const int    min_res_prec = 0;
    static const int    max_res_prec = 16;

    static QStringList functions = {"cos", "sin", "tan", "cot",
                                    "acos", "asin", "atan", "acot",
                                    "log", "log10", "log2", "exp", "sqrt"};
    enum functionsIndexes {cosFunc, sinFunc, tanFunc, cotFunc,
                           acosFunc, asinFunc, atanFunc, acotFunc,
                           logFunc, log10Func, log2Func, expFunc, sqrtFunc};
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * StringMath exception error class.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
class StringMathError
{
public:
    StringMathError(const QString &str) : msg(str) {}
    QString msg;
};

#endif // STRING_MATH_BASE_H
