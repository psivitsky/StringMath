#include "string_math.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] resultPrecision The precision of calculation result (an integer in range from 'min_res_prec' to 'max_res_prec').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMath::StringMath(int resultPrecision) : precision_(resultPrecision)
{
    set_precision(resultPrecision);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation precision setter function.
 * \param[in] resultPrecision The precision of calculation result (an integer in range from 'min_res_prec' to 'max_res_prec').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::set_precision(int resultPrecision)
{
    if(resultPrecision < min_res_prec)
        throw StringMathError("StringMath: the precision of calculation result is too low!");
    if(resultPrecision > max_res_prec)
        throw StringMathError("StringMath: the precision of calculation result is too big!");

    precision_ = resultPrecision;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constant adder function.\n
 * If the added constant already exists, its value will be replaced.
 * \param[in] constantName The constant name. It must contain from one to three characters.
 * \param[in] constantValue The constant value.
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
 * The constant remover function.
 * \param[in] constantName The constant name.
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
 * The function of calculating the expression.
 * \param[in] str Input expression of QString type.
 * \return The calculation result - a double value with 'res_prec' number of characters after the decimal point.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double StringMath::calculate(const QString &str)
{
    return 0.;
}
