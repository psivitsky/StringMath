#include "string_math_base.h"

double StringMathFuncImpl::cos_impl(double arg)
{
    return cos(arg);
}

double StringMathFuncImpl::sin_impl(double arg)
{
    return sin(arg);
}

double StringMathFuncImpl::tan_impl(double arg)
{
    if(abs(sin(arg)) == 1.)
        throw StringMathError("StringMathFuncImpl: the tangent is infinite!");
    return tan(arg);
};

double StringMathFuncImpl::cot_impl(double arg)
{
    if(abs(cos(arg)) == 1.)
        throw StringMathError("StringMathFuncImpl: the cotangent is infinite!");
    return 1. / tan(arg);
};

double StringMathFuncImpl::acos_impl(double arg)
{
    if(abs(arg) > 1.)
        throw StringMathError("StringMathFuncImpl: the arccosine subexpression "
                              "absolute value is greater than 1!");
    return acos(arg);
};

double StringMathFuncImpl::asin_impl(double arg)
{
    if(abs(arg) > 1.)
        throw StringMathError("StringMathFuncImpl: the arcsine subexpression "
                              "absolute value is greater than 1!");
    return asin(arg);
};

double StringMathFuncImpl::atan_impl(double arg)
{
    return atan(arg);
};
double StringMathFuncImpl::acot_impl(double arg)
{
    return atan(1. / arg);
};

double StringMathFuncImpl::log_impl(double arg)
{
    if(arg <= 0.)
        throw StringMathError(
            "StringMathFuncImpl: the natural logarithm subexpression value is "
            "less than or equal to zero!!");
    return log(arg);
};

double StringMathFuncImpl::log10_impl(double arg)
{
    if(arg <= 0.)
        throw StringMathError(
            "StringMathFuncImpl: the logarithm (base 10) subexpression value "
            "is less than or equal to zero!");
    return log10(arg);
};

double StringMathFuncImpl::log2_impl(double arg)
{
    if(arg <= 0.)
        throw StringMathError(
            "StringMathFuncImpl: the logarithm (base 2) subexpression value is "
            "less than or equal to zero!");
    return log2(arg);
};

double StringMathFuncImpl::exp_impl(double arg)
{
    return exp(arg);
};

double StringMathFuncImpl::sqrt_impl(double arg)
{
    if(arg < 0.)
        throw StringMathError("StringMathFuncImpl: the square root "
                              "subexpression value is negative!");
    return sqrt(arg);
};
