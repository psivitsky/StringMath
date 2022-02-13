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
 * The function of skipping the opening bracket.
 * \param[in,out] begin The iterator pointing to the first character in the processing string.
 * \param[in] end The iterator pointing to the character after the last character in the processing string.
 * \param[out] skippedStr Skipped characters (function name and the opening bracket).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void OpInterpreter::opening_bracket_skipping(QString::const_iterator &begin, QString::const_iterator end, QString &skippedStr) const
{
    while((*begin != opening_bracket) && (begin != end))
    {
        skippedStr += *begin;
        ++begin;
    }

    if(begin == end)
        throw StringMathError("OpInterpreter: there is no opening bracket!");

    skippedStr += *begin;
    ++begin;
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
 * \param[in,out] str The input string with spaces and the output string without spaces.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void OpInterpreter::spaces_removing(QString &str) const
{
    while(true)
    {
        if(str.isEmpty())
            break;

        if(str.at(0) == " ")
            str.remove(0, 1);
        else if(str.at(0) == "\t")
            str.remove(0, 1);
        else if(str.at(str.length() - 1) == " ")
            str.remove(str.length() - 1, 1);
        else if(str.at(str.length() - 1) == "\t")
            str.remove(str.length() - 1, 1);
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
    QRegExp checker("^(-)?\\d+(\\.\\d*)?$");
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

    throw StringMathError("OpInterpreter: the operand \"" + operand + "\" is invalid!");
}
