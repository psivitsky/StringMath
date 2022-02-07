#include "string_math_constant.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The default constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMathConstant::StringMathConstant() : value_(0.), name_("")
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] constantName The mathematical constant name.
 * \param[in] constantValue The mathematical constant value.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMathConstant::StringMathConstant(const QString &constantName, double constantValue) : value_(0.), name_("")
{
    set(constantName, constantValue);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The overload of the equality operator
 * \param[in] obj1 The left operand.
 * \param[in] obj2 The right operand.
 * \return The comparison result: true - operands have equal name and value, false - operands don't have equal name or value.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool operator==(const StringMathConstant &obj1, const StringMathConstant &obj2)
{
    if((obj1.name_ == obj2.name_) && (obj1.value_ == obj2.value_))
        return true;
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The mathematical constant setter function.
 * \param[in] constantName The mathematical constant name.
 * \param[in] constantValue The mathematical constant value.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMathConstant::set(const QString &constantName, double constantValue)
{
    set_name(constantName);
    set_value(constantValue);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The mathematical constant value getter function.
 * \return The mathematical constant value.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double StringMathConstant::value() const
{
    if(name_.isEmpty())
        throw StringMathError("StringMathConstant: the constant name is empty!");

    return value_;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The mathematical constant name setter function.
 * \param[in] constantName The mathematical constant name.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMathConstant::set_name(const QString &constantName)
{
    QRegExp checker("^\\w{1,3}$");
    if(!checker.exactMatch(constantName))
        throw StringMathError("StringMathConstant: invalid constant name!");

    name_ = constantName;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The mathematical constant name getter function.
 * \return The mathematical constant name.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
const QString &StringMathConstant::name() const
{
    if(name_.isEmpty())
        throw StringMathError("StringMathConstant: the constant name is empty!");

    return name_;
}
