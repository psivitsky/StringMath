#include "func_interpreter.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] functions The container with functions (StringMathFunction objects).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
FuncInterpreter::FuncInterpreter(const QVector<StringMathFunction> &functions) : functions_(functions)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function interpreter method.
 * \param[in,out] strExpression The expression string to interpret as input and the interpreted string as output.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FuncInterpreter::interpret(QString &strExpression) const
{
    QString name = "";
    extract_name(strExpression, name);
    check_name(name);

    double argument = extract_argument(strExpression);

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
