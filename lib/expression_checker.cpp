#include "expression_checker.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Operand parsing function.\n
 * The function removes spaces from the operand string, checks its syntax, and
 * replaces the constant if necessary.
 * \param[in] operandStr The operand string to parse.
 * \param[in] constants The container with constants.
 * \return A pointer to the expression operand.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionOperand*
ExpressionChecker::operand_parsing(const QString& operandStr,
                                   const QVector<StringMathConstant>& constants)
{
    double  new_operand_val = 0.;
    QString new_operand_str = operandStr;
    spaces_removing(new_operand_str);

    if(new_operand_str.isEmpty())
        return new ExpressionOperand;

    QRegExp checker("^(-)?\\d+(\\.\\d*)?$");
    if(checker.exactMatch(new_operand_str))
        new_operand_val = new_operand_str.toDouble();
    else
    {
        bool f_constant_replaced = false;
        foreach(StringMathConstant constant, constants)
        {
            if(constant.name() == new_operand_str)
            {
                new_operand_val = constant.value();
                f_constant_replaced = true;

                break;
            }
        }

        if(!f_constant_replaced)
            throw StringMathError("ExpressionChecker: the operand \"" +
                                  new_operand_str + "\" is invalid!");
    }

    ExpressionOperand* symbol = new ExpressionOperand;
    symbol->set_value(new_operand_val);

    return symbol;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Spaces removing function.
 * \param[in,out] str The input string with spaces and
 * the output string without spaces.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionChecker::spaces_removing(QString& str)
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
 * \param[in] begin The iterator pointing to the operand in the parsing
 * container.
 * \param[in] end The iterator pointing to a symbol after the last
 * symbol in the parsing container.
 * \return Pointer to the operand.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionOperand* ExpressionChecker::operand_checking(
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
 * Operator checking function.
 * \param[in] begin The iterator pointing to the operator in the parsing
 * container.
 * \param[in] end The iterator pointing to a symbol after the last
 * symbol in the parsing container.
 * \return centerOperator Pointer to the operator.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionOperator* ExpressionChecker::operator_checking(
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
