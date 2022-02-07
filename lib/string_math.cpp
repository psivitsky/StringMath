#include "string_math.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] precisionValue The precision of calculation result (an integer value in range from 'min_precision_value' to 'max_precision_value').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMath::StringMath(int precisionValue)
{
    set_precision(precisionValue);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation precision setter function.
 * \param[in] precisionValue The precision of calculation result (an integer value in range from 'min_precision_value' to 'max_precision_value').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::set_precision(int precisionValue)
{
    if(precisionValue < min_precision_value)
        throw StringMathError("StringMath: the precision of calculation result is too small!");
    if(precisionValue > max_precision_value)
        throw StringMathError("StringMath: the precision of calculation result is too big!");

    precision_ = precisionValue;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation constant adder function.
 * \param[in] newConstant The new constant.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::add_constant(const StringMathConstant &newConstant)
{
    if(newConstant.name().isEmpty())
        throw StringMathError("StringMath: the constant name is empty!");

    foreach(StringMathConstant constant, constants_)
    {
        if(newConstant.name() == constant.name())
            throw StringMathError("StringMath: such a constant already exists!");
    }

    constants_.push_back(newConstant);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation constant replacer function.
 * \param[in] existingConstantName The name of existing constant.
 * \param[in] newConstantValue The new value.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::replace_constant(const QString &existingConstantName, double newConstantValue)
{
    foreach(StringMathConstant constant, constants_)
    {
        if(constant.name() == existingConstantName)
        {
            constant.set_value(newConstantValue);
            return;
        }
    }

    throw StringMathError("StringMath: there is no such constant for replacement!");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation constant remover function.
 * \param[in] existingConstant The existing constant.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::remove_constant(const StringMathConstant &existingConstant)
{
    if(!constants_.contains(existingConstant))
        throw StringMathError("StringMath: there is no such constant for removal!");

    constants_.removeOne(existingConstant);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function adder function.
 * \param[in] newFunction The new function.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::add_function(const StringMathFunction &newFunction)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function replacer function.
 * \param[in] existingFunctionName The name of existing function.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::replace_function(const QString &existingFunctionName, std::function<double (double)> newFunction)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function remover function.
 * \param[in] newFunction The existing function.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::remove_function(const StringMathFunction &newFunction)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of calculating the expression.
 * \param[in] strExpression The expression of QString type.
 * \param[out] calcResult The calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::calculate(const QString &strExpression, QString &calcResult) const
{
    ExpressionAnalyzer obj(precision_, constants_, functions_);
    obj.analyze(strExpression, calcResult);
}
