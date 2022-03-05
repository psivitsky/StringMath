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
void FROpInterpreter::interpret(const QVector<ExpressionSymbol*>& symbolsBefore,
                                QVector<ExpressionSymbol*>& symbolsAfter) const
{
    if(symbolsBefore.isEmpty())
        throw StringMathError("FROpInterpreter: the expression is empty!");

    if(!symbolsAfter.isEmpty())
    {
        foreach(ExpressionSymbol* symbol, symbolsAfter)
            delete symbol;
        symbolsAfter.clear();
    }

    QVector<ExpressionSymbol*>::const_iterator iterator = symbolsBefore.begin();

    ExpressionOperand* left_operand =
        operand_checker(iterator, symbolsBefore.end());
    ++iterator;

    ExpressionOperator* expression_operator = nullptr;
    ExpressionOperand*  right_operand = nullptr;

    while(iterator != symbolsBefore.end())
    {
        expression_operator = operator_checker(iterator, symbolsBefore.end());
        ++iterator;
        right_operand = operand_checker(iterator, symbolsBefore.end());
        ++iterator;

        if(first_rank_operators.contains(expression_operator->operator_type()))
        {
            left_operand = first_rank_operation_processing(
                left_operand, expression_operator, right_operand);
        }
        else if(second_rank_operators.contains(
                    expression_operator->operator_type()))
        {
            symbolsAfter.push_back(left_operand);
            symbolsAfter.push_back(expression_operator);

            left_operand = right_operand;
        }
        else
            throw StringMathError("FROpInterpreter: the expression contains an "
                                  "invalid operator!");
    }

    symbolsAfter.push_back(left_operand);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Operator checker function.
 * \param[in] begin The iterator pointing to the operator in the parsing
 * container.
 * \param[in] end The iterator pointing to a symbol after the last
 * symbol in the parsing container.
 * \return centerOperator Pointer to the operator.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionOperator* FROpInterpreter::operator_checker(
    QVector<ExpressionSymbol*>::const_iterator begin,
    QVector<ExpressionSymbol*>::const_iterator end) const
{
    if(begin == end)
        throw StringMathError("FROpInterpreter: the expression syntax error!");

    ExpressionOperator* expression_operator = 0;

    if((*begin)->symbol_type() == operatorType)
        expression_operator = dynamic_cast<ExpressionOperator*>(*begin);
    else
        throw StringMathError("FROpInterpreter: the expression syntax error!");

    return expression_operator;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Operand checker function.
 * \param[in] begin The iterator pointing to the operand in the parsing
 * container.
 * \param[in] end The iterator pointing to a symbol after the last
 * symbol in the parsing container.
 * \return Pointer to the operand.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionOperand* FROpInterpreter::operand_checker(
    QVector<ExpressionSymbol*>::const_iterator begin,
    QVector<ExpressionSymbol*>::const_iterator end) const
{
    if(begin == end)
        throw StringMathError("FROpInterpreter: the expression syntax error!");

    ExpressionOperand* operand = 0;

    if((*begin)->symbol_type() == operandType)
        operand = dynamic_cast<ExpressionOperand*>(*begin);
    else
        throw StringMathError("FROpInterpreter: the expression syntax error!");

    return operand;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The first rank operation processing function.\n
 * \param[in] leftOperand Pointer to the left operand.
 * \param[in] centerOperator Pointer to the first rank operator.
 * \param[in] rightOperand Pointer to the right operand.
 * \return Pointer to the new operand.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionOperand* FROpInterpreter::first_rank_operation_processing(
    const ExpressionOperand*  leftOperand,
    const ExpressionOperator* centerOperator,
    const ExpressionOperand*  rightOperand) const
{
    if(leftOperand->is_empty())
        throw StringMathError("FROpInterpreter: the expression syntax error!");

    if(rightOperand->is_empty())
        throw StringMathError("FROpInterpreter: the expression syntax error!");

    ExpressionOperand* new_operand = new ExpressionOperand;

    if(centerOperator->operator_type() == multType)
        new_operand->set_value(leftOperand->value() * rightOperand->value());
    else if(centerOperator->operator_type() == divType)
        new_operand->set_value(leftOperand->value() / rightOperand->value());
    else
        throw StringMathError(
            "FROpInterpreter: there is no such first rank operator!");

    return new_operand;
}
