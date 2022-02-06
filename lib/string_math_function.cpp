#include "string_math_function.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The default constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMathFunction::StringMathFunction() : name_("")
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] functionName The algebraic function name.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMathFunction::StringMathFunction(const QString &functionName)
{
    set_name(functionName);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The operator==() overload function.
 * \param[in] obj1 The left operand.
 * \param[in] obj2 The right operand.
 * \return The comparison result: true - operands have equal name, false - operands don't have equal name.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool operator==(const StringMathFunction &obj1, const StringMathFunction &obj2)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function name setter function.
 * \param[in] constantName The algebraic function name.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMathFunction::set_name(const QString &constantName)
{

}
