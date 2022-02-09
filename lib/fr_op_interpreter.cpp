#include "fr_op_interpreter.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] constants The container with constants (StringMathConstant objects).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
FROpInterpreter::FROpInterpreter(const QVector<StringMathConstant> &constants) : OpInterpreter(constants)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * First rang operators interpreter function.
 * \param[in] expressionStr The expression string to interpret.
 * \param[out] interpretedExpStr The interpreted expression string.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FROpInterpreter::interpret(const QString &expressionStr, QString &interpretedExpStr) const
{
    interpretedExpStr = "";
    for(QString::const_iterator i = expressionStr.begin(); i != expressionStr.end(); ++i)
    {
        //The first rang operator finder.
        //If operator is found...
            //Operands extraction.
            //Constants replacement.
            //Operands check.
            //Calculation.
        interpretedExpStr += *i;
    }
}
