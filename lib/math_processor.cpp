#include "math_processor.h"

double operators_processing(const QVector<ExpressionSymbol*>&);
double
function_processing(double, const QString&, const QVector<StringMathFunction>&);

ExpressionOperand* operand_checking(QVector<ExpressionSymbol*>::const_iterator,
                                    QVector<ExpressionSymbol*>::const_iterator);
ExpressionOperator*
    operator_checking(QVector<ExpressionSymbol*>::const_iterator);

void hyper_1_operation_processing(ExpressionOperand*,
                                  const ExpressionOperator*,
                                  const ExpressionOperand*,
                                  double&);
void hyper_2_operation_processing(ExpressionOperand*,
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
    const Expression&                  expression,
    const QVector<StringMathFunction>& functions)
{
    foreach(ExpressionSymbol* symbol, expression.symbols())
    {
        if(symbol->symbol_type() == expressionType)
        {
            Expression* subexpression = dynamic_cast<Expression*>(symbol);
            subexpression->set_value(
                expression_calculation(*subexpression, functions));
        }
    }

    double calc_result = operators_processing(expression.symbols());

    calc_result =
        function_processing(calc_result, expression.function_name(), functions);

    switch(std::fpclassify(calc_result))
    {
        case FP_INFINITE:
            throw StringMathError(
                "MathProcessor: the calculation result is infinite!");
        case FP_NAN:
            throw StringMathError(
                "MathProcessor: the calculation result is not a number!");
        default:
            break;
    }

    return calc_result;
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
    if(symbols.isEmpty())
        throw StringMathError("MathProcessor: the expression is empty!");

    double calc_result = 0.;

    QVector<ExpressionSymbol*>::const_iterator begin = symbols.begin();
    QVector<ExpressionSymbol*>::const_iterator end = symbols.end();

    ExpressionOperand* left_operand = operand_checking(begin, end);
    ++begin;

    ExpressionOperator* expression_operator = nullptr;
    ExpressionOperand*  right_operand = nullptr;

    while(begin != end)
    {
        expression_operator = operator_checking(begin);
        ++begin;
        right_operand = operand_checking(begin, end);
        ++begin;

        if(MathProcessor::hyper_1_operators.contains(
               expression_operator->operator_type()))
        {
            if(left_operand->is_empty() && (left_operand == symbols.first()))
                left_operand->set_value(0.);

            hyper_1_operation_processing(left_operand,
                                         expression_operator,
                                         right_operand,
                                         calc_result);
        }
        else if(MathProcessor::hyper_2_operators.contains(
                    expression_operator->operator_type()))
        {
            hyper_2_operation_processing(left_operand,
                                         expression_operator,
                                         right_operand);
        }
        else
            throw StringMathError("MathProcessor: the expression contains an "
                                  "invalid operator!");
    }

    if(left_operand->is_empty())
        throw StringMathError("MathProcessor: the left operand is empty!");
    calc_result += left_operand->value();

    return calc_result;
}
//----------------------------------------------------------------------------------
/*!
 * The method of processing the algebraic function.
 * \param[in] argument The algebraic function argument.
 * \param[in] name The algebraic function name.
 * \param[in] functions The container with functions.
 * \return The result of the calculation.
 */
//----------------------------------------------------------------------------------
double function_processing(double                             argument,
                           const QString&                     name,
                           const QVector<StringMathFunction>& functions)
{
    double calc_result = 0.;
    if(name.isEmpty())
        calc_result = argument;
    else
    {
        bool f_calculated = false;
        foreach(StringMathFunction function, functions)
        {
            if(function.name() == name)
            {
                calc_result = function.calculate(argument);
                f_calculated = true;
                break;
            }
        }

        if(!f_calculated)
            throw StringMathError("MathProcessor: the function \"" + name +
                                  "\" doesn't exist!");
    }

    return calc_result;
}
//----------------------------------------------------------------------------------
/*!
 * Operand checking function.
 * \param[in] begin The iterator pointing to the operand in the parsing
 * container.
 * \param[in] end The iterator pointing to a symbol after the last
 * symbol in the parsing container.
 * \return Pointer to the operand.
 */
//----------------------------------------------------------------------------------
ExpressionOperand*
operand_checking(QVector<ExpressionSymbol*>::const_iterator begin,
                 QVector<ExpressionSymbol*>::const_iterator end)
{
    if(begin == end)
        throw StringMathError("MathProcessor: the operand is missing!");

    ExpressionOperand* operand = nullptr;
    if((*begin)->symbol_type() == operandType)
        operand = dynamic_cast<ExpressionOperand*>(*begin);
    else if((*begin)->symbol_type() == expressionType)
        operand = dynamic_cast<ExpressionOperand*>(*begin);
    else
        throw StringMathError("MathProcessor: the operand is missing!");

    return operand;
}
//----------------------------------------------------------------------------------
/*!
 * Operator checking function.
 * \param[in] iterator The iterator pointing to the operator in the parsing
 * container.
 * \return Pointer to the operator.
 */
//----------------------------------------------------------------------------------
ExpressionOperator*
operator_checking(QVector<ExpressionSymbol*>::const_iterator iterator)
{
    ExpressionOperator* expression_operator = nullptr;
    if((*iterator)->symbol_type() == operatorType)
        expression_operator = dynamic_cast<ExpressionOperator*>(*iterator);
    else
        throw StringMathError("MathProcessor: the operator is missing!");

    return expression_operator;
}
//----------------------------------------------------------------------------------
/*!
 * The hyper 1 operation processing function.
 * \param[in,out] leftOperand Pointer to the current left operand at the input
 * and the next left operand at the output.
 * \param[in] centerOperator Pointer to the hyper 1 operator.
 * \param[in] rightOperand Pointer to the right operand.
 * \param[in,out] calcResult The calculation result.
 */
//----------------------------------------------------------------------------------
void hyper_1_operation_processing(ExpressionOperand*        leftOperand,
                                  const ExpressionOperator* centerOperator,
                                  const ExpressionOperand*  rightOperand,
                                  double&                   calcResult)
{
    if(leftOperand->is_empty())
        throw StringMathError("MathProcessor: the left operand is empty!");

    if(rightOperand->is_empty())
        throw StringMathError("MathProcessor: the right operand is empty!");

    calcResult += leftOperand->value();

    if(centerOperator->operator_type() == sumType)
        leftOperand->set_value(rightOperand->value());
    else if(centerOperator->operator_type() == diffType)
        leftOperand->set_value(-rightOperand->value());
    else
        throw StringMathError(
            "MathProcessor: there is no such hyper 1 operation!");
}
//----------------------------------------------------------------------------------
/*!
 * The hyper 2 operation processing function.
 * \param[in,out] leftOperand Pointer to the current left operand at the input
 * and the next left operand at the output.
 * \param[in] centerOperator Pointer to the hyper 2 operator.
 * \param[in] rightOperand Pointer to the right operand.
 */
//----------------------------------------------------------------------------------
void hyper_2_operation_processing(ExpressionOperand*        leftOperand,
                                  const ExpressionOperator* centerOperator,
                                  const ExpressionOperand*  rightOperand)
{
    if(leftOperand->is_empty())
        throw StringMathError("MathProcessor: the left operand is empty!");

    if(rightOperand->is_empty())
        throw StringMathError("MathProcessor: the right operand is empty!");

    if(centerOperator->operator_type() == multType)
        leftOperand->set_value(leftOperand->value() * rightOperand->value());
    else if(centerOperator->operator_type() == divType)
        leftOperand->set_value(leftOperand->value() / rightOperand->value());
    else
        throw StringMathError(
            "MathProcessor: there is no such hyper 2 operation!");
}
