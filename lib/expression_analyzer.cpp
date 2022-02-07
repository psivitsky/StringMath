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
    precision_(precision), constants_(constants), functions_(functions)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The expression analyzer function.
 * \param[in] begin The expression string begin.
 * \param[in] end The expression string begin.
 * \param[in] calcResult The calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::analyze(QString::const_iterator begin, QString::const_iterator end, QString &calcResult) const
{
    subexpression_finder();

    constants_replacer();

    first_rang_operators.interpret(begin, end);
    second_rang_operators.interpret(begin, end);
    function.interpret(begin, end);

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
