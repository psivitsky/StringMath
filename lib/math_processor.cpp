#include "math_processor.h"
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

    FROpInterpreter first_rank_operators_;
    first_rank_operators_.interpret(symbols_to_interpret, interpreted_symbols);

    SROpInterpreter second_rank_operators_;
    double calc_result = second_rank_operators_.interpret(interpreted_symbols);

    FuncInterpreter function_(functions);
    return function_.interpret(calc_result, expression->function_name());
}
