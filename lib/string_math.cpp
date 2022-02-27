#include "string_math.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details Constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMath::StringMath()
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
    QString            calcResult;
    ExpressionAnalyzer obj(max_precision, constants_, functions_);
    obj.analyze(strExpression, calcResult);

    return calcResult.toDouble();
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
QString& StringMath::calculate(const QString& strExpression,
                               int            precision) const
{
    static QString     calcResult;
    ExpressionAnalyzer obj(precision, constants_, functions_);
    obj.analyze(strExpression, calcResult);

    return calcResult;
}
