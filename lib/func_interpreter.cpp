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
    QString::const_iterator begin = expressionStr.begin();

    QString name = "";
    if(expressionStr.contains(opening_bracket))
        extract_name(begin, expressionStr.end(), name);

    double argument = extract_argument(begin, expressionStr.end());

    calculate(name, argument, interpretedExpStr);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function name extractor method.\n
 * The function name is located before the opening bracket.
 * \param[in,out] begin The iterator pointing to the first character in the processing string.
 * \param[in] end The iterator pointing to the character after the last character in the processing string.
 * \param[out] funcName The function name (without spaces).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FuncInterpreter::extract_name(QString::const_iterator &begin, QString::const_iterator end, QString &funcName) const
{
    funcName = "";

    while((*begin != opening_bracket) && (begin != end))
    {
        funcName += *begin;
        ++begin;
    }

    if(begin == end)
        throw StringMathError("FuncInterpreter: there is no opening bracket!");

    ++begin;        //Skipping the opening bracket.

    spaces_removing(funcName);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function argument extractor method.\n
 * If the expression does not contain a function, then the expression itself is an argument.
 * If the expression contains a function, then the argument is between brackets.
 * \param[in] begin The iterator pointing to the character in the processing string (after the opening bracket).
 * \param[in] end The iterator pointing to the character after the last character in the processing string.
 * \return The function argument value.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double FuncInterpreter::extract_argument(QString::const_iterator begin, QString::const_iterator end) const
{
    QString argument = "";
    while((begin != end) || (*begin != closing_bracket))
    {
        argument += *begin;
        ++begin;
    }

    operand_processing(argument);

    return argument.toDouble();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function calculation method.\n
 * If the function name is empty, then there is no function in the expression. The function calculation result will be the argument.
 * \param[in] funcName The function name.
 * \param[in] funcArgument The function argument value.
 * \param[out] calcResultStr The algebraic function calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FuncInterpreter::calculate(const QString &funcName, double funcArgument, QString &calcResultStr) const
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
                calc_result = function.calculate(funcArgument);
        }

        if(!f_calculated)
            throw StringMathError("FuncInterpreter: the function \"" + funcName + "\" doesn't exist!");
    }

    calcResultStr = QString::number(calc_result, 'f', precision);
}
