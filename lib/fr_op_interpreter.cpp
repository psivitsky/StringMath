#include "fr_op_interpreter.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
FROpInterpreter::FROpInterpreter()
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * First rang operators interpreter function.
 * \param[in,out] strExpression The expression string to interpret.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FROpInterpreter::interpret(QString &strExpression) const
{
    QString result = "";
    for(QString::const_iterator i = strExpression.begin(); i != strExpression.end(); ++i)
    {
        //The first rang operator finder.
        //If operator is found...
            //Operands extraction.
            //Calculation.
        result += *i;
    }
}
