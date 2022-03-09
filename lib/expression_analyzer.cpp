#include "expression_analyzer.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] precisionValue The precision of calculation result (an integer
 * non-negative value).
 * \param[in] constants The container with constants (StringMathConstant
 * objects).
 * \param[in] functions The container with functions (StringMathFunction
 * objects).
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionAnalyzer::ExpressionAnalyzer(
    int precision, const QVector<StringMathConstant>& constants,
    const QVector<StringMathFunction>& functions)
    : precision_(precision), function_(functions), constants_(constants),
      functions_(functions)
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The expression analyzer function.
 * \param[in] expressionStr The expression string to analyze.
 * \param[in] calcResultStr The calculation result.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::analyze(const QString& expressionStr,
                                 QString&       calcResultStr) const
{
    Expression* expression =
        MathParser::expression_parsing(expressionStr, constants_);

    calcResultStr = QString::number(calculate(expression, ""), 'f', precision_);
}

double ExpressionAnalyzer::calculate(const Expression* expression,
                                     const QString&    funcName) const
{
    QVector<ExpressionSymbol*> symbols_without_subexpressions;

    foreach(ExpressionSymbol* symbol, expression->symbols())
    {
        if(symbol->symbol_type() == expressionType)
        {
            Expression* subexpression = dynamic_cast<Expression*>(symbol);
            ExpressionOperand* operand = new ExpressionOperand;
            operand->set_value(
                calculate(subexpression, subexpression->function_name()));

            symbols_without_subexpressions.push_back(operand);
        }
        else
            symbols_without_subexpressions.push_back(symbol);
    }

    QVector<ExpressionSymbol*> interpreted_symbols;
    first_rank_operators_.interpret(symbols_without_subexpressions,
                                    interpreted_symbols);

    double calc_result = second_rank_operators_.interpret(interpreted_symbols);
    calc_result = function_.interpret(calc_result, funcName);

    return calc_result;
}
