#include "math_processor.h"

double operators_processing(const QVector<ExpressionSymbol*>&);

ExpressionOperand* hyper_1_operation_processing(const ExpressionOperand*,
                                                const ExpressionOperator*,
                                                const ExpressionOperand*,
                                                double&);

ExpressionOperand* hyper_2_operation_processing(const ExpressionOperand*,
                                                const ExpressionOperator*,
                                                const ExpressionOperand*);

//----------------------------------------------------------------------------------
/*!
 * Expression calculation function.
 * \param[in] expression The expression to calculate.
 * \param[in] functions The container with functions.
 * \return The result of the calculation.
 */
//----------------------------------------------------------------------------------
double MathProcessor::expression_calculation(
    const Expression* expression, const QVector<StringMathFunction>& functions)
{
    QVector<ExpressionSymbol*> symbols_to_interpret;
    QVector<ExpressionSymbol*> interpreted_symbols;

    foreach(ExpressionSymbol* symbol, expression->symbols())
    {
        if(symbol->symbol_type() == expressionType)
        {
            double subexpression_val = expression_calculation(
                dynamic_cast<Expression*>(symbol), functions);

            ExpressionOperand* operand = new ExpressionOperand();
            operand->set_value(subexpression_val);

            symbols_to_interpret.push_back(operand);
        }
        else
            symbols_to_interpret.push_back(symbol);
    }

    double calc_result = operators_processing(symbols_to_interpret);

    FuncInterpreter function_(functions);
    return function_.interpret(calc_result, expression->function_name());
}
//----------------------------------------------------------------------------------
/*!
 * The function of processing expression operators.
 * \param[in] symbols The expression to calculate.
 * \return The result of the calculation.
 */
//----------------------------------------------------------------------------------
double operators_processing(const QVector<ExpressionSymbol*>& symbols)
{
    double calc_result = 0.;

    if(symbols.isEmpty())
        throw StringMathError("MathProcessor: the expression is empty!");

    QVector<ExpressionSymbol*>::const_iterator iterator = symbols.begin();

    ExpressionOperand* left_operand =
        MathChecker::operand_checking(iterator, symbols.end());
    ++iterator;

    ExpressionOperator* expression_operator = nullptr;
    ExpressionOperand*  right_operand = nullptr;

    while(iterator != symbols.end())
    {
        expression_operator =
            MathChecker::operator_checking(iterator, symbols.end());
        ++iterator;
        right_operand = MathChecker::operand_checking(iterator, symbols.end());
        ++iterator;

        if(MathProcessor::hyper_1_operators.contains(
               expression_operator->operator_type()))
        {
            if(left_operand->is_empty() && (symbols.first() == left_operand))
                left_operand->set_value(0.);

            left_operand = hyper_1_operation_processing(
                left_operand, expression_operator, right_operand, calc_result);
        }
        else if(MathProcessor::hyper_2_operators.contains(
                    expression_operator->operator_type()))
        {
            left_operand = hyper_2_operation_processing(
                left_operand, expression_operator, right_operand);
        }
        else
            throw StringMathError("MathProcessor: the expression contains an "
                                  "invalid operator!");
    }

    calc_result += left_operand->value();

    return calc_result;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The hyper 1 operation processing function.
 * \param[in] leftOperand Pointer to the left operand.
 * \param[in] centerOperator Pointer to the hyper 1 operator.
 * \param[in] rightOperand Pointer to the right operand.
 * \param[in,out] calcResult The calculation result.
 * \return Pointer to the new left operand.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionOperand*
hyper_1_operation_processing(const ExpressionOperand*  leftOperand,
                             const ExpressionOperator* centerOperator,
                             const ExpressionOperand*  rightOperand,
                             double&                   calcResult)
{
    if(leftOperand->is_empty())
        throw StringMathError("MathProcessor: the left operand is empty!");

    if(rightOperand->is_empty())
        throw StringMathError("MathProcessor: the right operand is empty!");

    calcResult += leftOperand->value();

    ExpressionOperand* new_operand = new ExpressionOperand(*rightOperand);

    if(centerOperator->operator_type() == diffType)
        new_operand->set_value(-rightOperand->value());

    return new_operand;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The hyper 2 operation processing function.
 * \param[in] leftOperand Pointer to the left operand.
 * \param[in] centerOperator Pointer to the hyper 2 operator.
 * \param[in] rightOperand Pointer to the right operand.
 * \return Pointer to the new left operand.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionOperand*
hyper_2_operation_processing(const ExpressionOperand*  leftOperand,
                             const ExpressionOperator* centerOperator,
                             const ExpressionOperand*  rightOperand)
{
    if(leftOperand->is_empty())
        throw StringMathError("MathProcessor: the left operand is empty!");

    if(rightOperand->is_empty())
        throw StringMathError("MathProcessor: the right operand is empty!");

    ExpressionOperand* new_operand = new ExpressionOperand();

    if(centerOperator->operator_type() == multType)
        new_operand->set_value(leftOperand->value() * rightOperand->value());
    else if(centerOperator->operator_type() == divType)
        new_operand->set_value(leftOperand->value() / rightOperand->value());
    else
        throw StringMathError(
            "MathProcessor: there is no such hyper 2 operation!");

    return new_operand;
}
