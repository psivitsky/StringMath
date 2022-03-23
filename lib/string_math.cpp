#include "string_math.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details Constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMath::StringMath()
    : constants_({StringMathConstant("pi", 3.1415926535897932384626433832795),
                  StringMathConstant("e", 2.7182818284590452353602874713527)}),
      functions_({StringMathFunction("cos", StringMathFuncImpl::cos_impl),
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
                  StringMathFunction("sqrt", StringMathFuncImpl::sqrt_impl)})
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of adding a constant.
 * \param[in] newConstant The new constant.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::add_constant(const StringMathConstant& newConstant)
{
    if(newConstant.name().isEmpty())
        throw StringMathError("StringMath: the constant name is empty!");

    foreach(StringMathConstant constant, constants_)
    {
        if(newConstant.name() == constant.name())
            throw StringMathError(
                "StringMath: such a constant already exists!");
    }

    constants_.push_back(newConstant);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Constant replacement function.
 * \param[in] existingConstantName The name of an existing constant.
 * \param[in] newConstantValue New constant value.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::replace_constant(const QString& existingConstantName,
                                  double         newConstantValue)
{
    bool f_replaced = false;
    foreach(StringMathConstant constant, constants_)
    {
        if(constant.name() == existingConstantName)
        {
            constant.set_value(newConstantValue);
            f_replaced = true;
            break;
        }
    }

    if(!f_replaced)
        throw StringMathError(
            "StringMath: there is no such constant for replacement!");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Constant remover function.
 * \param[in] existingConstant An existing constant.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::remove_constant(const StringMathConstant& existingConstant)
{
    if(!constants_.contains(existingConstant))
        throw StringMathError(
            "StringMath: there is no such constant for removal!");

    constants_.removeOne(existingConstant);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of getting constants.
 * \return The container with constants ('StringMathConstant' objects).
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
const QVector<StringMathConstant>& StringMath::constants() const
{
    return constants_;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Method of adding a function.
 * \param[in] newFunction The new function.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::add_function(const StringMathFunction& newFunction)
{
    if(newFunction.name().isEmpty())
        throw StringMathError("StringMath: the function name is empty!");

    foreach(StringMathFunction function, functions_)
    {
        if(newFunction.name() == function.name())
            throw StringMathError(
                "StringMath: such a function already exists!");
    }

    functions_.push_back(newFunction);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Method of replacing the function.
 * \param[in] existingFunctionName The name of existing function.
 * \param[in] newFunction The function wrapper.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::replace_function(const QString& existingFunctionName,
                                  std::function<double(double)> newFunction)
{
    bool f_replaced = false;
    foreach(StringMathFunction function, functions_)
    {
        if(function.name() == existingFunctionName)
        {
            function.set_function(newFunction);
            f_replaced = true;
            break;
        }
    }

    if(!f_replaced)
        throw StringMathError(
            "StringMath: there is no such function for replacement!");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Function remover method.
 * \param[in] newFunction An existing function.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::remove_function(const StringMathFunction& existingFunction)
{
    if(!functions_.contains(existingFunction))
        throw StringMathError(
            "StringMath: there is no such function for removal!");

    functions_.removeOne(existingFunction);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The method of getting functions.
 * \return The container with functions ('StringMathFunction' objects).
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
const QVector<StringMathFunction>& StringMath::functions() const
{
    return functions_;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Expression calculation function.
 * \param[in] strExpression Expression string.
 * \return The result of the calculation ('double' value).
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
double StringMath::calculate(const QString& strExpression) const
{
    Expression* expression =
        MathParser::expression_parsing(strExpression, constants_);

    return MathProcessor::expression_calculation(expression, functions_);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Expression calculation function.
 * \param[in] strExpression Expression string.
 * \param[in] precision Calculation precision (non-negative integer value
 * between 'min_precision' and 'max_precision').
 * \return The result of the calculation (string).
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
QString StringMath::calculate(const QString& strExpression, int precision) const
{
    return QString::number(calculate(strExpression), 'f', precision);
}
