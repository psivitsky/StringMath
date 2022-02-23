#include "fr_op_interpreter.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
FROpInterpreter::FROpInterpreter()
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * First rank operators interpreter function.
 * \param[in] symbolsBefore Expression symbols to interpret.
 * \param[out] symbolsAfter Interpreted expression symbols.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FROpInterpreter::interpret(const QVector<StringMathSymbol> &symbolsBefore, QVector<StringMathSymbol> &symbolsAfter) const
{
    symbolsAfter.clear();

    if(symbolsBefore.isEmpty())
        throw StringMathError("FROpInterpreter: the expression is empty!");

    StringMathSymbol    left_operand;
    StringMathSymbol    center_operator;
    StringMathSymbol    right_operand;

    QVector<StringMathSymbol>::const_iterator iterator = symbolsBefore.begin();

    left_operand = *iterator;
    ++iterator;

    while(true)
    {
        if(iterator == symbolsBefore.end())
        {
            symbolsAfter.push_back(left_operand);
            break;
        }

        operation_parser(iterator, symbolsBefore.end(), center_operator, right_operand);

        if(first_rank_operators.contains(center_operator.type))
            first_rank_operation_processing(left_operand, center_operator, right_operand);
        else if(second_rank_operators.contains(center_operator.type))
            second_rank_operation_processing(left_operand, center_operator, right_operand, symbolsAfter);
        else
            throw StringMathError("FROpInterpreter: the expression contains an invalid operator!");
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic operation parser function.\n
 * An algebraic operation consists of three elements: a left operand, an operator, and a right operand.
 * The left operand is already known, so the function extracts the operator and the right operand.\n
 * After parsing, the iterator "begin" will be pointing to the next operator.
 * \param[in,out] begin The iterator pointing to the operator in the parsing container.
 * \param[in] end The iterator pointing to a symbol after the last symbol in the parsing container.
 * \param[out] centerOperator The operator.
 * \param[out] rightOperand The right operand.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FROpInterpreter::operation_parser(QVector<StringMathSymbol>::const_iterator &begin,
                                       QVector<StringMathSymbol>::const_iterator end,
                                       StringMathSymbol &centerOperator,
                                       StringMathSymbol &rightOperand) const
{
    centerOperator = *begin;
    ++begin;

    if(begin == end)
        throw StringMathError("FROpInterpreter: the right operand is missing!");

    rightOperand = *begin;
    ++begin;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The first rank algebraic operation processing function.\n
 * The processing result will be stored in the "leftOperand" structure.
 * \param[in,out] leftOperand The left operand.
 * \param[in] centerOperator The first rank operator.
 * \param[in] rightOperand The right operand.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FROpInterpreter::first_rank_operation_processing(StringMathSymbol &leftOperand,
                                                      const StringMathSymbol &centerOperator,
                                                      const StringMathSymbol &rightOperand) const
{
    if(leftOperand.type != operandType)
        throw StringMathError("FROpInterpreter: the left operand is invalid!");

    if(rightOperand.type != operandType)
        throw StringMathError("FROpInterpreter: the right operand is invalid!");

    double calc_result = 0.;
    if(centerOperator.type == multOperatorType)
        calc_result = leftOperand.value * rightOperand.value;
    else if(centerOperator.type == divOperatorType)
        calc_result = leftOperand.value / rightOperand.value;
    else
        throw StringMathError("FROpInterpreter: there is no such first rank operator!");

    leftOperand.value = calc_result;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The second rank algebraic operation processing function.
 * \param[in,out] leftOperand The left operand.
 * \param[in] centerOperator The second rank operator.
 * \param[in] rightOperand The right operand.
 * \param[out] symbolsAfter Interpreted expression symbols.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void FROpInterpreter::second_rank_operation_processing(StringMathSymbol &leftOperand, const StringMathSymbol &centerOperator,
                                                       const StringMathSymbol &rightOperand, QVector<StringMathSymbol> &symbolsAfter) const
{
    if((leftOperand.type != operandType) && (leftOperand.type != emptyOperandType))
        throw StringMathError("FROpInterpreter: the left operand is invalid!");

    if(rightOperand.type != operandType)
        throw StringMathError("FROpInterpreter: the right operand is invalid!");

    symbolsAfter.push_back(leftOperand);
    symbolsAfter.push_back(centerOperator);
    leftOperand = rightOperand;
}
