#include "sr_op_interpreter.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
SROpInterpreter::SROpInterpreter()
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Second rank operators interpreter function.
 * \param[in] symbols Expression symbols to interpret.
 * \return The calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double SROpInterpreter::interpret(const QVector<StringMathSymbol> &symbols) const
{
    QVector<StringMathSymbol>::const_iterator iterator = symbols.begin();

    StringMathSymbol first_operand = *iterator;
    if(first_operand.type == emptyOperandType)
    {
        first_operand.type = operandType;
        first_operand.value = 0.;
    }

    if(first_operand.type != operandType)
        throw StringMathError("SROpInterpreter: the operand is invalid!");

    double calc_result = first_operand.value;

    ++iterator;
    while(iterator != symbols.end())
    {
        if(iterator->type == sumOperatorType)
        {
            ++iterator;

            if(iterator == symbols.end())
                throw StringMathError("SROpInterpreter: an operand is missing!");

            if(iterator->type != operandType)
                throw StringMathError("SROpInterpreter: the operand is invalid!");

            calc_result += iterator->value;
        }
        else if(iterator->type == diffOperatorType)
        {
            ++iterator;

            if(iterator == symbols.end())
                throw StringMathError("SROpInterpreter: an operand is missing!");

            if(iterator->type != operandType)
                throw StringMathError("SROpInterpreter: the operand is invalid!");

            calc_result -= iterator->value;
        }
        else
            throw StringMathError("SROpInterpreter: there is no such second rank operator!");

        ++iterator;
    }

    return calc_result;
}
