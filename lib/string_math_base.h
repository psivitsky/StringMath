#ifndef STRING_MATH_BASE_H
#define STRING_MATH_BASE_H

#include    <QString>
#include    <QtCore/qglobal.h>

#include    <cmath>

#if defined(STRINGMATH_LIBRARY)
#  define STRINGMATH_EXPORT Q_DECL_EXPORT
#else
#  define STRINGMATH_EXPORT Q_DECL_IMPORT
#endif

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * StringMath exception error class.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
class StringMathError
{
public:
    StringMathError(const QString &str) : msg(str) {}
    const QString &what() { return msg; }
private:
    QString msg;
};

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * StringMathFunction implementations.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
namespace StringMathFuncImpl
{
static double cos_impl(double arg) { return cos(arg); };
static double sin_impl(double arg) { return sin(arg); };

static double tan_impl(double arg)
{
    if(abs(sin(arg)) == 1.)
        throw StringMathError("StringMathFuncImpl: the tangent is infinite!");
    return tan(arg);
};

static double cot_impl(double arg)
{
    if(abs(cos(arg)) == 1.)
        throw StringMathError("StringMathFuncImpl: the cotangent is infinite!");
    return 1. / tan(arg);
};

static double acos_impl(double arg)
{
    if(abs(arg) > 1.)
        throw StringMathError("StringMathFuncImpl: the arccosine subexpression absolute value is greater than 1!");
    return acos(arg);
};

static double asin_impl(double arg)
{
    if(abs(arg) > 1.)
        throw StringMathError("StringMathFuncImpl: the arcsine subexpression absolute value is greater than 1!");
    return asin(arg);
};

static double atan_impl(double arg) { return atan(arg); };
static double acot_impl(double arg) { return atan(1. / arg); };

static double log_impl(double arg)
{
    if(arg <= 0.)
        throw StringMathError("StringMathFuncImpl: the natural logarithm subexpression value is less than or equal to zero!!");
    return log(arg);
};

static double log10_impl(double arg)
{
    if(arg <= 0.)
        throw StringMathError("StringMathFuncImpl: the logarithm (base 10) subexpression value is less than or equal to zero!");
    return log10(arg);
};

static double log2_impl(double arg)
{
    if(arg <= 0.)
        throw StringMathError("StringMathFuncImpl: the logarithm (base 2) subexpression value is less than or equal to zero!");
    return log2(arg);
};

static double exp_impl(double arg) { return exp(arg); };

static double sqrt_impl(double arg)
{
    if(arg < 0.)
        throw StringMathError("StringMathFuncImpl: the square root subexpression value is negative!");
    return sqrt(arg);
};
}

#endif // STRING_MATH_BASE_H
