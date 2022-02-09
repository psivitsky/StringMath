#include "func_interpreter.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] constants The container with constants (StringMathConstant objects).
 * \param[in] functions The container with functions (StringMathFunction objects).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
FuncInterpreter::FuncInterpreter(const QVector<StringMathConstant> &constants, const QVector<StringMathFunction> &functions) :
    OpInterpreter(constants), functions_(functions)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function interpreter method.
 * \param[in] expressionStr The expression string to interpret.
 * \param[out] interpretedExpStr The interpreted expression string.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FuncInterpreter::interpret(const QString &expressionStr, QString &interpretedExpStr) const
{
    QString name = "";
    extract_name(expressionStr, name);
    check_name(name);

    double argument = extract_argument(expressionStr);

    foreach(StringMathFunction function, functions_)
    {
        if(function.name() == name)
            ;       // Function calculation
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function name extractor method.\n
 * The function name is located before the opening bracket.
 * \param[in] strExpression The expression string.
 * \param[out] funcName The funtion name.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FuncInterpreter::extract_name(const QString &strExpression, QString &funcName) const
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function name checker method.
 * \param[in] funcName The funtion name.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FuncInterpreter::check_name(const QString &funcName) const
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function argument extractor method.\n
 * The function argument is located between brackets.
 * \param[in] strExpression The expression string.
 * \return The function argument.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double FuncInterpreter::extract_argument(const QString &strExpression) const
{

}
