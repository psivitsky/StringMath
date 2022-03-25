#include "string_math_constant.h"
//----------------------------------------------------------------------------------
//! \details The default constructor.
//----------------------------------------------------------------------------------
StringMathConstant::StringMathConstant() : value_(0.), name_("")
{
}
//----------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] constantName Constant name.
 * \param[in] constantValue Constant value.
 */
//----------------------------------------------------------------------------------
StringMathConstant::StringMathConstant(const QString& constantName,
                                       double         constantValue)
    : value_(0.), name_("")
{
    set(constantName, constantValue);
}
//----------------------------------------------------------------------------------
/*!
 * Overload of the equality operator.
 * \param[in] obj1 The left operand.
 * \param[in] obj2 The right operand.
 * \return The comparison result:
 * true - operands have equal name and value,
 * false - operands don't have equal name or value.
 */
//----------------------------------------------------------------------------------
bool operator==(const StringMathConstant& obj1, const StringMathConstant& obj2)
{
    if((obj1.name_ == obj2.name_) && (obj1.value_ == obj2.value_))
        return true;
    return false;
}
//----------------------------------------------------------------------------------
/*!
 * Constant setter function.
 * \param[in] constantName Constant name.
 * \param[in] constantValue Constant value.
 */
//----------------------------------------------------------------------------------
void StringMathConstant::set(const QString& constantName, double constantValue)
{
    set_name(constantName);
    set_value(constantValue);
}
//----------------------------------------------------------------------------------
/*!
 * The function of setting a constant value.
 * \param[in] value Constant value.
 */
//----------------------------------------------------------------------------------
void StringMathConstant::set_value(double value)
{
    value_ = value;
}
//----------------------------------------------------------------------------------
/*!
 * The function of getting the constant value.
 * \return Constant value.
 */
//----------------------------------------------------------------------------------
double StringMathConstant::value() const
{
    if(name_.isEmpty())
        throw StringMathError(
            "StringMathConstant: the constant name is empty!");

    return value_;
}
//----------------------------------------------------------------------------------
/*!
 * The function of setting a constant name.
 * \param[in] constantName Constant name.
 */
//----------------------------------------------------------------------------------
void StringMathConstant::set_name(const QString& constantName)
{
    QRegExp checker_1("^\\d{1,3}$");
    if(checker_1.exactMatch(constantName))
        throw StringMathError("StringMathConstant: a constant name consisting "
                              "of digits is meaningless!");

    QRegExp checker_2("^\\w{1,3}$");
    if(!checker_2.exactMatch(constantName))
        throw StringMathError("StringMathConstant: invalid constant name!");

    name_ = constantName;
}
//----------------------------------------------------------------------------------
/*!
 * The function of getting the constant name.
 * \return Constant name.
 */
//----------------------------------------------------------------------------------
const QString& StringMathConstant::name() const
{
    if(name_.isEmpty())
        throw StringMathError(
            "StringMathConstant: the constant name is empty!");

    return name_;
}
