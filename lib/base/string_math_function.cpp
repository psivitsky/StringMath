#include "string_math_function.h"

#include <QRegExp>

#include <utility>

//----------------------------------------------------------------------------------
//! \details The default constructor.
//----------------------------------------------------------------------------------
StringMathFunction::StringMathFunction() : name_(""), function_(nullptr)
{
}
//----------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] functionName Function name.
 * \param[in] function Function implementation.
 */
//----------------------------------------------------------------------------------
StringMathFunction::StringMathFunction(const QString& functionName,
                                       std::function<double(double)> function)
    : name_(""), function_(nullptr)
{
    set_name(functionName);
    set_function(std::move(function));
}
//----------------------------------------------------------------------------------
/*!
 * Overload of the equality operator.
 * \param[in] obj1 The left operand.
 * \param[in] obj2 The right operand.
 * \return The comparison result:
 * true - operands have equal name and function,
 * false - operands don't have equal name or function.
 */
//----------------------------------------------------------------------------------
bool operator==(const StringMathFunction& obj1, const StringMathFunction& obj2)
{
    return (obj1.name_ == obj2.name_) &&
           (&(obj1.function_) == &(obj2.function_));
}
//----------------------------------------------------------------------------------
/*!
 * Function setter method.
 * \param[in] functionName Function name.
 * \param[in] function Function implementation.
 */
//----------------------------------------------------------------------------------
void StringMathFunction::set(const QString&                functionName,
                             std::function<double(double)> function)
{
    set_name(functionName);
    set_function(std::move(function));
}
//----------------------------------------------------------------------------------
/*!
 * The method of setting a function name.
 * \param[in] functionName Function name.
 */
//----------------------------------------------------------------------------------
void StringMathFunction::set_name(const QString& functionName)
{
    QRegExp checker_1("^\\d{1,5}$");
    if(checker_1.exactMatch(functionName))
        throw StringMathError("StringMathFunction: a function name consisting "
                              "of digits is meaningless!");

    QRegExp checker_2("^\\w{1,5}$");
    if(!checker_2.exactMatch(functionName))
        throw StringMathError("StringMathFunction: invalid function name!");

    name_ = functionName;
}
//----------------------------------------------------------------------------------
/*!
 * The method of getting the function name.
 * \return Function name.
 */
//----------------------------------------------------------------------------------
const QString& StringMathFunction::name() const
{
    if(name_.isEmpty())
        throw StringMathError(
            "StringMathFunction: the function name is empty!");

    return name_;
}
//----------------------------------------------------------------------------------
/*!
 * The method of setting a function implementation.
 * \param[in] function Function implementation.
 */
//----------------------------------------------------------------------------------
void StringMathFunction::set_function(std::function<double(double)> function)
{
    function_ = std::move(function);
}
//----------------------------------------------------------------------------------
/*!
 * The method of getting the function implementation.
 * \return Function implementation.
 */
//----------------------------------------------------------------------------------
std::function<double(double)> StringMathFunction::function() const
{
    if(name_.isEmpty())
        throw StringMathError(
            "StringMathFunction: the function name is empty!");

    return function_;
}
//----------------------------------------------------------------------------------
/*!
 * Function calculator.
 * \param[in] argument Function argument.
 * \return The result of calculating the function.
 */
//----------------------------------------------------------------------------------
double StringMathFunction::calculate(double argument) const
{
    double result = function_(argument);
    return result;
}
