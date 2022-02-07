#include "string_math_function.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The default constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMathFunction::StringMathFunction() : name_(""), function_(0)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] functionName The algebraic function name.
 * \param[in] function The algebraic function implementation.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMathFunction::StringMathFunction(const QString &functionName, std::function<double (double)> function) : name_(""), function_(0)
{
    set_name(functionName);
    set_function(function);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The overload of the equality operator.
 * \param[in] obj1 The left operand.
 * \param[in] obj2 The right operand.
 * \return The comparison result: true - operands have equal name and function, false - operands don't have equal name or function.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool operator==(const StringMathFunction &obj1, const StringMathFunction &obj2)
{
    if((obj1.name_ == obj2.name_) && (&(obj1.function_) == &(obj2.function_)))
        return true;
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function setter.
 * \param[in] functionName The algebraic function name.
 * \param[in] function The algebraic function implementation.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMathFunction::set(const QString &functionName, std::function<double (double)> function)
{
    set_name(functionName);
    set_function(function);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function name setter.
 * \param[in] functionName The algebraic function name.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMathFunction::set_name(const QString &functionName)
{
    QRegExp checker("^\\w{1,5}$");
    if(!checker.exactMatch(functionName))
        throw StringMathError("StringMathFunction: invalid function name!");

    name_ = functionName;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function name getter.
 * \return The algebraic function name.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
const QString &StringMathFunction::name() const
{
    if(name_.isEmpty())
        throw StringMathError("StringMathFunction: the function name is empty!");

    return name_;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function implementation getter.
 * \return The algebraic function implementation.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
std::function<double (double)> StringMathFunction::function() const
{
    return function_;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function calculator.
 * \param[in] argument The algebraic function argument.
 * \return The algebraic function calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double StringMathFunction::calculate(double argument) const
{
    double result = function_(argument);

    switch(std::fpclassify(result))
    {
        case FP_INFINITE:
            throw StringMathError("StringMathFunction: \"" + name_ + "\" calculation result is infinite!");
        case FP_NAN:
            throw StringMathError("StringMathFunction: \"" + name_ + "\" calculation result is not a number!");
        default:
            break;
    }

    return result;
}
