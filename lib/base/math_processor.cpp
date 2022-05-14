#include "math_processor.h"

double operators_calculation(const QVector<ExpressionSymbol*>&);

ExpressionOperand* operand_checking(QVector<ExpressionSymbol*>::const_iterator,
                                    QVector<ExpressionSymbol*>::const_iterator);
ExpressionOperator*
    operator_checking(QVector<ExpressionSymbol*>::const_iterator);

double operators_processing(QVector<ExpressionSymbol*>::const_iterator&,
                            QVector<ExpressionSymbol*>::const_iterator);

double operator_calculation(const ExpressionOperand*,
                            const ExpressionOperator*,
                            const ExpressionOperand*);
double hyper_1_operator_calculation(const ExpressionOperand*,
                                    const ExpressionOperator*,
                                    const ExpressionOperand*);
double hyper_2_operator_calculation(const ExpressionOperand*,
                                    const ExpressionOperator*,
                                    const ExpressionOperand*);
double hyper_3_operator_calculation(const ExpressionOperand*,
                                    const ExpressionOperator*,
                                    const ExpressionOperand*);

double function_calculation(double,
                            const QString&,
                            const QVector<StringMathFunction>&);

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

    double calc_result = operators_calculation(expression.symbols());

    calc_result = function_calculation(calc_result,
                                       expression.function_name(),
                                       functions);

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
 * The function of calculation expression operators.
 * \param[in] symbols The expression symbols.
 * \return The result of the calculation.
 */
//----------------------------------------------------------------------------------
double operators_calculation(const QVector<ExpressionSymbol*>& symbols)
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
        calc_result = operators_processing(begin, end);

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
 * The function of processing expression operators.\n
 * It is guaranteed that the expression contains more than one symbol.
 * \param[in,out] begin The iterator pointing to the left operand.
 * \param[in] end The iterator pointing to a symbol after the last
 * symbol in the parsing container.
 * \return The result of the processing.
 * \warning
 * The code is too complex.\n
 * The function modifies operands and operators.
 */
//----------------------------------------------------------------------------------
double operators_processing(QVector<ExpressionSymbol*>::const_iterator& begin,
                            QVector<ExpressionSymbol*>::const_iterator  end)
{
    ExpressionOperand* l_val = operand_checking(begin, end);
    ++begin;

    ExpressionOperator* l_op = operator_checking(begin);
    ++begin;

    double calc_result = 0.;
    while(true)
    {
        ExpressionOperand* r_val = operand_checking(begin, end);
        ++begin;

        if(begin == end)
        {
            calc_result = operator_calculation(l_val, l_op, r_val);
            break;
        }

        ExpressionOperator* r_op = operator_checking(begin);
        ++begin;

        if(l_op->operator_rank() == r_op->operator_rank())
        {
            l_val->set_value(operator_calculation(l_val, l_op, r_val));
            *l_op = *r_op;
        }
        else if(l_op->operator_rank() < r_op->operator_rank())
        {
            begin -= 2;
            r_val->set_value(operators_processing(begin, end));

            if(begin == end)
            {
                calc_result = operator_calculation(l_val, l_op, r_val);
                break;
            }
            else
            {
                l_val->set_value(operator_calculation(l_val, l_op, r_val));

                ++begin;
                l_op = operator_checking(begin);
                ++begin;
            }
        }
        else
        {
            calc_result = operator_calculation(l_val, l_op, r_val);

            r_val->set_value(calc_result);
            begin -= 2;

            break;
        }
    }

    return calc_result;
}
//----------------------------------------------------------------------------------
/*!
 * Operator calculation function.
 * \param[in] lVal Pointer to the left operand.
 * \param[in] op Pointer to the operator.
 * \param[in] rVal Pointer to the right operand.
 * \return The calculation result.
 */
//----------------------------------------------------------------------------------
double operator_calculation(const ExpressionOperand*  lVal,
                            const ExpressionOperator* op,
                            const ExpressionOperand*  rVal)
{
    double calc_result = 0.;
    if(op->operator_rank() == hyper1)
        calc_result = hyper_1_operator_calculation(lVal, op, rVal);
    else if(op->operator_rank() == hyper2)
        calc_result = hyper_2_operator_calculation(lVal, op, rVal);
    else if(op->operator_rank() == hyper3)
        calc_result = hyper_3_operator_calculation(lVal, op, rVal);
    return calc_result;
}

//----------------------------------------------------------------------------------
/*!
 * The hyper 1 operator calculation function.
 * \param[in] lVal Pointer to the left operand.
 * \param[in] op Pointer to the hyper 1 operator.
 * \param[in] rVal Pointer to the right operand.
 * \return The calculation result.
 */
//----------------------------------------------------------------------------------
double hyper_1_operator_calculation(const ExpressionOperand*  lVal,
                                    const ExpressionOperator* op,
                                    const ExpressionOperand*  rVal)
{
    if(lVal->is_empty())
        throw StringMathError("MathProcessor: the left operand is empty!");

    if(rVal->is_empty())
        throw StringMathError("MathProcessor: the right operand is empty!");

    double result = 0.;
    if(op->operator_type() == sumType)
        result = lVal->value() + rVal->value();
    else if(op->operator_type() == diffType)
        result = lVal->value() - rVal->value();
    else
        throw StringMathError(
            "MathProcessor: there is no such hyper 1 operation!");

    return result;
}
//----------------------------------------------------------------------------------
/*!
 * The hyper 2 operator calculation function.
 * \param[in] lVal Pointer to the left operand.
 * \param[in] op Pointer to the hyper 2 operator.
 * \param[in] rVal Pointer to the right operand.
 * \return The calculation result.
 */
//----------------------------------------------------------------------------------
double hyper_2_operator_calculation(const ExpressionOperand*  lVal,
                                    const ExpressionOperator* op,
                                    const ExpressionOperand*  rVal)
{
    if(lVal->is_empty())
        throw StringMathError("MathProcessor: the left operand is empty!");

    if(rVal->is_empty())
        throw StringMathError("MathProcessor: the right operand is empty!");

    double result = 0.;
    if(op->operator_type() == multType)
        result = lVal->value() * rVal->value();
    else if(op->operator_type() == divType)
        result = lVal->value() / rVal->value();
    else
        throw StringMathError(
            "MathProcessor: there is no such hyper 2 operation!");

    return result;
}
//----------------------------------------------------------------------------------
/*!
 * The hyper 3 operator calculation function.
 * \param[in] lVal Pointer to the left operand.
 * \param[in] op Pointer to the hyper 3 operator.
 * \param[in] rVal Pointer to the right operand.
 * \return The calculation result.
 */
//----------------------------------------------------------------------------------
double hyper_3_operator_calculation(const ExpressionOperand*  lVal,
                                    const ExpressionOperator* op,
                                    const ExpressionOperand*  rVal)
{
    if(lVal->is_empty())
        throw StringMathError("MathProcessor: the left operand is empty!");

    if(rVal->is_empty())
        throw StringMathError("MathProcessor: the right operand is empty!");

    double result = 0.;
    if(op->operator_type() == powType)
        result = pow(lVal->value(), rVal->value());
    else
        throw StringMathError(
            "MathProcessor: there is no such hyper 3 operation!");
    return result;
}
//----------------------------------------------------------------------------------
/*!
 * The method of calculation the algebraic function.
 * \param[in] argument The algebraic function argument.
 * \param[in] name The algebraic function name.
 * \param[in] functions The container with functions.
 * \return The result of the calculation.
 */
//----------------------------------------------------------------------------------
double function_calculation(double                             argument,
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
