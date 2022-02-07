#include "expression_analyzer.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] precisionValue The precision of calculation result (an integer non-negative value).
 * \param[in] constants The container with constants (StringMathConstant objects).
 * \param[in] functions The container with functions (StringMathFunction objects).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
ExpressionAnalyzer::ExpressionAnalyzer(int precision, const QVector<StringMathConstant> &constants, const QVector<StringMathFunction> &functions) :
    precision_(precision), function_(functions), constants_(constants), functions_(functions)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The expression analyzer function.
 * \param[in] strExpression The expression string to analyze.
 * \param[in] calcResult The calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::analyze(const QString &strExpression, QString &calcResult) const
{
    QString temp_str = strExpression;

    subexpression_finder();

    constants_replacer();

    first_rang_operators_.interpret(temp_str);
    second_rang_operators_.interpret(temp_str);
    function_.interpret(temp_str);

    rounder();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The subexpression finder function.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::subexpression_finder() const
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The mathematical constants replacer function.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::constants_replacer() const
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The expression calculation result rounder function.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::rounder() const
{

}
