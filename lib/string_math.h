//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Mathematical expression calculation
 * \details
 * Class description
 * -----
 * The class object performs calculations from a given mathematical expression
 * in string format. The result of the calculation can be a 'double' value or a
 * string with a given precision.
 *
 * The expression can contain subexpresions in brackets of diffrent types
 * ('()', '[]' and '{}'). The object can compute functions (see 'functions_'
 * list). Their names are taken from MATLAB. The object also supports constants
 * such as 'pi' (see 'constants_' list).
 *
 * You can add, replace, or remove constants and functions via the class
 * interface. For more information, see classes 'StringMathConstant' and
 * 'StringMathFunction'.
 *
 * If the object finds a syntax error or, for example, a division by zero, it
 * throws an exception of the 'StringMathError' type.
 *
 * Code example
 * -----
 * \code
 * try
 * {
 *     QString exp_str = "6/2*(2+1)";
 *
 *     StringMath obj;
 *     double result = obj.calculate(exp_str);
 *     //The result will be 9.
 * }
 * catch(StringMathError &err)
 * {
 *     //Error handling (use err.what()).
 * }
 * \endcode
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef STRING_MATH_H
#define STRING_MATH_H

#include "expression_analyzer.h"

class STRINGMATH_EXPORT StringMath
{
public:
    StringMath();
    // Functions...
    void add_constant(const StringMathConstant& newConstant);
    void replace_constant(const QString& existingConstantName,
                          double         newConstantValue);
    void remove_constant(const StringMathConstant& existingConstant);
    const QVector<StringMathConstant>& constants() const;

    void add_function(const StringMathFunction& newFunction);
    void replace_function(const QString&                existingFunctionName,
                          std::function<double(double)> newFunction);
    void remove_function(const StringMathFunction& existingFunction);
    const QVector<StringMathFunction>& functions() const;

    double   calculate(const QString& strExpression) const;
    QString& calculate(const QString& strExpression, int precision) const;

private:
    StringMath(const StringMath& obj);
    StringMath& operator=(const StringMath& obj);
    // Constants...
    static const int min_precision = 0;
    static const int max_precision = 16;
    // Containers...
    QVector<StringMathConstant> constants_ = {
        StringMathConstant("pi", 3.1415926535897932384626433832795),
        StringMathConstant("e", 2.7182818284590452353602874713527)};

    QVector<StringMathFunction> functions_ = {
        StringMathFunction("cos", StringMathFuncImpl::cos_impl),
        StringMathFunction("sin", StringMathFuncImpl::sin_impl),
        StringMathFunction("tan", StringMathFuncImpl::tan_impl),
        StringMathFunction("cot", StringMathFuncImpl::cot_impl),
        StringMathFunction("acos", StringMathFuncImpl::acos_impl),
        StringMathFunction("asin", StringMathFuncImpl::asin_impl),
        StringMathFunction("atan", StringMathFuncImpl::atan_impl),
        StringMathFunction("acot", StringMathFuncImpl::acot_impl),
        StringMathFunction("log", StringMathFuncImpl::log_impl),
        StringMathFunction("log10", StringMathFuncImpl::log10_impl),
        StringMathFunction("log2", StringMathFuncImpl::log2_impl),
        StringMathFunction("exp", StringMathFuncImpl::exp_impl),
        StringMathFunction("sqrt", StringMathFuncImpl::sqrt_impl)};
};
#endif // STRING_MATH_H
