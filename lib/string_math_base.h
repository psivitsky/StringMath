#ifndef STRING_MATH_BASE_H
#define STRING_MATH_BASE_H

#include <QtCore/qglobal.h>

#if defined(STRINGMATH_LIBRARY)
#define STRINGMATH_EXPORT Q_DECL_EXPORT
#else
#define STRINGMATH_EXPORT Q_DECL_IMPORT
#endif

#include <QString>

#include <cmath>

//----------------------------------------------------------------------------------
//! \details StringMath exception error class.
//----------------------------------------------------------------------------------
class StringMathError
{
public:
    StringMathError(const QString& str) : msg(str)
    {
    }
    const QString& what()
    {
        return msg;
    }

private:
    QString msg;
};

//----------------------------------------------------------------------------------
//! \details StringMathFunction implementations.
//----------------------------------------------------------------------------------
namespace StringMathFuncImpl
{

double cos_impl(double arg);
double sin_impl(double arg);
double tan_impl(double arg);
double cot_impl(double arg);
double acos_impl(double arg);
double asin_impl(double arg);
double atan_impl(double arg);
double acot_impl(double arg);
double log_impl(double arg);
double log10_impl(double arg);
double log2_impl(double arg);
double exp_impl(double arg);
double sqrt_impl(double arg);

} // namespace StringMathFuncImpl

#endif // STRING_MATH_BASE_H
