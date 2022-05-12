#include "math_processor.h"

double operators_processing(const QVector<ExpressionSymbol*>&);
double
function_processing(double, const QString&, const QVector<StringMathFunction>&);

ExpressionOperand* operand_checking(QVector<ExpressionSymbol*>::const_iterator,
                                    QVector<ExpressionSymbol*>::const_iterator);
ExpressionOperator*
    operator_checking(QVector<ExpressionSymbol*>::const_iterator);

double operators_calculation(QVector<ExpressionSymbol*>::const_iterator&,
                             QVector<ExpressionSymbol*>::const_iterator);

double operation_switcher(const ExpressionOperand*,
                          const ExpressionOperator*,
                          const ExpressionOperand*);

double hyper_1_operation_processing(const ExpressionOperand*,
                                    const ExpressionOperator*,
                                    const ExpressionOperand*);
double hyper_2_operation_processing(const ExpressionOperand*,
                                    const ExpressionOperator*,
                                    const ExpressionOperand*);
double hyper_3_operation_processing(const ExpressionOperand*,
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

    QVector<ExpressionSymbol*>::const_iterator begin = symbols.begin();
    QVector<ExpressionSymbol*>::const_iterator end = symbols.end();

    ExpressionOperand* left_operand = operand_checking(begin, end);
    if(symbols.size() == 1)
    {
        if(left_operand->is_empty())
            throw StringMathError("MathProcessor: the operand is empty!");

        return left_operand->value();
    }
    else
    {
        if(left_operand->is_empty())
            left_operand->set_value(0.);
    }

    double calc_result = 0.;
    while(begin != end)
        calc_result = operators_calculation(begin, end);

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
 * The function of calculating expression operators.
 * \param[in,out] begin The iterator pointing to the left operand.
 * \param[in] end The iterator pointing to a symbol after the last
 * symbol in the parsing container.
 * \return The result of the calculation.
 */
//----------------------------------------------------------------------------------
double operators_calculation(QVector<ExpressionSymbol*>::const_iterator& begin,
                             QVector<ExpressionSymbol*>::const_iterator  end)
{
    double calc_result = 0.;

    ExpressionOperand* left_operand = operand_checking(begin, end);
    ++begin;

    ExpressionOperator* left_operator = operator_checking(begin);
    ++begin;

    while(true)
    {
        ExpressionOperand* right_operand = operand_checking(begin, end);
        ++begin;

        if(begin == end)
        {
            calc_result =
                operation_switcher(left_operand, left_operator, right_operand);
            break;
        }

        ExpressionOperator* right_operator = operator_checking(begin);
        ++begin;

        if(left_operator->operator_rank() == right_operator->operator_rank())
        {
            left_operand->set_value(
                operation_switcher(left_operand, left_operator, right_operand));
            *left_operator = *right_operator;
        }
        else if(left_operator->operator_rank() <
                right_operator->operator_rank())
        {
            begin -= 2;
            right_operand->set_value(operators_calculation(begin, end));

            if(begin == end)
            {
                calc_result = operation_switcher(left_operand,
                                                 left_operator,
                                                 right_operand);
                break;
            }
            else
            {
                left_operand->set_value(operation_switcher(left_operand,
                                                           left_operator,
                                                           right_operand));

                begin += 1;
                left_operator = operator_checking(begin);
                begin += 1;
            }
        }
        else
        {
            calc_result =
                operation_switcher(left_operand, left_operator, right_operand);

            right_operand->set_value(calc_result);
            begin -= 2;

            break;
        }
    }

    return calc_result;
}
//----------------------------------------------------------------------------------
/*!
 * Operator type selection function.
 * \param[in] leftOperand Pointer to the left operand.
 * \param[in] centerOperator Pointer to the operator.
 * \param[in] rightOperand Pointer to the right operand.
 * \return The calculation result.
 */
//----------------------------------------------------------------------------------
double operation_switcher(const ExpressionOperand*  leftOperand,
                          const ExpressionOperator* centerOperator,
                          const ExpressionOperand*  rightOperand)
{
    double calc_result = 0.;
    if(centerOperator->operator_rank() == hyper1)
        calc_result = hyper_1_operation_processing(leftOperand,
                                                   centerOperator,
                                                   rightOperand);
    else if(centerOperator->operator_rank() == hyper2)
        calc_result = hyper_2_operation_processing(leftOperand,
                                                   centerOperator,
                                                   rightOperand);
    else if(centerOperator->operator_rank() == hyper3)
        calc_result = hyper_3_operation_processing(leftOperand,
                                                   centerOperator,
                                                   rightOperand);
    return calc_result;
}

//----------------------------------------------------------------------------------
/*!
 * The hyper 1 operation processing function.
 * \param[in] leftOperand Pointer to the left operand.
 * \param[in] centerOperator Pointer to the hyper 1 operator.
 * \param[in] rightOperand Pointer to the right operand.
 * \return The calculation result.
 */
//----------------------------------------------------------------------------------
double hyper_1_operation_processing(const ExpressionOperand*  leftOperand,
                                    const ExpressionOperator* centerOperator,
                                    const ExpressionOperand*  rightOperand)
{
    if(leftOperand->is_empty())
        throw StringMathError("MathProcessor: the left operand is empty!");

    if(rightOperand->is_empty())
        throw StringMathError("MathProcessor: the right operand is empty!");

    double result = 0.;
    if(centerOperator->operator_type() == sumType)
        result = leftOperand->value() + rightOperand->value();
    else if(centerOperator->operator_type() == diffType)
        result = leftOperand->value() - rightOperand->value();
    else
        throw StringMathError(
            "MathProcessor: there is no such hyper 1 operation!");

    return result;
}
//----------------------------------------------------------------------------------
/*!
 * The hyper 2 operation processing function.
 * \param[in] leftOperand Pointer to the left operand.
 * \param[in] centerOperator Pointer to the hyper 2 operator.
 * \param[in] rightOperand Pointer to the right operand.
 * \return The calculation result.
 */
//----------------------------------------------------------------------------------
double hyper_2_operation_processing(const ExpressionOperand*  leftOperand,
                                    const ExpressionOperator* centerOperator,
                                    const ExpressionOperand*  rightOperand)
{
    if(leftOperand->is_empty())
        throw StringMathError("MathProcessor: the left operand is empty!");

    if(rightOperand->is_empty())
        throw StringMathError("MathProcessor: the right operand is empty!");

    double result = 0.;
    if(centerOperator->operator_type() == multType)
        result = leftOperand->value() * rightOperand->value();
    else if(centerOperator->operator_type() == divType)
        result = leftOperand->value() / rightOperand->value();
    else
        throw StringMathError(
            "MathProcessor: there is no such hyper 2 operation!");

    return result;
}
//----------------------------------------------------------------------------------
/*!
 * The hyper 3 operation processing function.
 * \param[in] leftOperand Pointer to the left operand.
 * \param[in] centerOperator Pointer to the hyper 3 operator.
 * \param[in] rightOperand Pointer to the right operand.
 * \return The calculation result.
 */
//----------------------------------------------------------------------------------
double hyper_3_operation_processing(const ExpressionOperand*  leftOperand,
                                    const ExpressionOperator* centerOperator,
                                    const ExpressionOperand*  rightOperand)
{
    if(leftOperand->is_empty())
        throw StringMathError("MathProcessor: the left operand is empty!");

    if(rightOperand->is_empty())
        throw StringMathError("MathProcessor: the right operand is empty!");

    double result = 0.;
    if(centerOperator->operator_type() == powType)
        result = pow(leftOperand->value(), rightOperand->value());
    else
        throw StringMathError(
            "MathProcessor: there is no such hyper 3 operation!");
    return result;
}
