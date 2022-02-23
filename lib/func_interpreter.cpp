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
 * \param[in] expressionStr The expression string to interpret.
 * \param[out] interpretedExpStr The interpreted expression string.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double FuncInterpreter::interpret(double funcArgument, const QString &funcName) const
{
    double calc_result = 0.;
    if(funcName.isEmpty())
        calc_result = funcArgument;
    else
    {
        bool f_calculated = false;
        foreach(StringMathFunction function, functions_)
        {
            if(function.name() == funcName)
            {
                calc_result = function.calculate(funcArgument);
                f_calculated = true;
                break;
            }
        }

        if(!f_calculated)
            throw StringMathError("FuncInterpreter: the function \"" + funcName + "\" doesn't exist!");
    }

    return calc_result;
}
