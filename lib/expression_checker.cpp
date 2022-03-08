#include "expression_checker.h"
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
ExpressionOperand* ExpressionChecker::operand_checker(
    QVector<ExpressionSymbol*>::const_iterator begin,
    QVector<ExpressionSymbol*>::const_iterator end)
{
    if(begin == end)
        throw StringMathError(
            "ExpressionChecker: the expression syntax error!");

    ExpressionOperand* operand = 0;

    if((*begin)->symbol_type() == operandType)
        operand = dynamic_cast<ExpressionOperand*>(*begin);
    else
        throw StringMathError(
            "ExpressionChecker: the expression syntax error!");

    return operand;
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
ExpressionOperator* ExpressionChecker::operator_checker(
    QVector<ExpressionSymbol*>::const_iterator begin,
    QVector<ExpressionSymbol*>::const_iterator end)
{
    if(begin == end)
        throw StringMathError(
            "ExpressionChecker: the expression syntax error!");

    ExpressionOperator* expression_operator = 0;

    if((*begin)->symbol_type() == operatorType)
        expression_operator = dynamic_cast<ExpressionOperator*>(*begin);
    else
        throw StringMathError(
            "ExpressionChecker: the expression syntax error!");

    return expression_operator;
}
