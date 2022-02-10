#include "op_interpreter.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] constants The container with constants (StringMathConstant objects).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
OpInterpreter::OpInterpreter(const QVector<StringMathConstant> &constants) : constants_(constants)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Operand processing function.
 * \param[in,out] operand The operand string at the input and the processing result at the output.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void OpInterpreter::operand_processing(QString &operand) const
{
    spaces_removing(operand);
    if(!operand_checking(operand))
        constant_replacing(operand);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Spaces removing function.
 * \param[in,out] operand Operand string at the input and the operand string without spaces at the output.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void OpInterpreter::spaces_removing(QString &operand) const
{
    while(true)
    {
        if(operand.isEmpty())
            break;

        if(operand.at(0) == " ")
            operand.remove(0, 1);
        else if(operand.at(operand.length() - 1) == " ")
            operand.remove(operand.length() - 1, 1);
        else
            break;
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Operand checking function.
 * \param[in] operand The operand string.
 * \return Check result: true - the operand is alright, false - the operand is invalid.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool OpInterpreter::operand_checking(const QString &operand) const
{
    QRegExp checker("^\\d+(.\\d*)?$");
    if(checker.exactMatch(operand))
        return true;
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Constant replacement function.
 * \param[in,out] operand The operand string at the input and the replacement result at the output.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void OpInterpreter::constant_replacing(QString &operand) const
{
    foreach(StringMathConstant constant, constants_)
    {
        if(constant.name() == operand)
        {
            operand = QString::number(constant.value(), 'f', precision);
            return;
        }
    }

    throw StringMathError("OpInterpreter: the operand " + operand + " is invalid!");
}
