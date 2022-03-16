#include "math_processor.h"

double MathProcessor::expression_calculation(
    const Expression* expression, const QVector<StringMathFunction>& functions)
{
    QVector<ExpressionSymbol*> symbols_without_subexpressions;

    foreach(ExpressionSymbol* symbol, expression->symbols())
    {
        if(symbol->symbol_type() == expressionType)
        {
            Expression* subexpression = dynamic_cast<Expression*>(symbol);
            ExpressionOperand* operand = new ExpressionOperand;
            operand->set_value(
                expression_calculation(subexpression, functions));

            symbols_without_subexpressions.push_back(operand);
        }
        else
            symbols_without_subexpressions.push_back(symbol);
    }

    FuncInterpreter function_(functions);
    FROpInterpreter first_rank_operators_;
    SROpInterpreter second_rank_operators_;

    QVector<ExpressionSymbol*> interpreted_symbols;
    first_rank_operators_.interpret(symbols_without_subexpressions,
                                    interpreted_symbols);

    double calc_result = second_rank_operators_.interpret(interpreted_symbols);
    calc_result = function_.interpret(calc_result, expression->function_name());

    return calc_result;
}
