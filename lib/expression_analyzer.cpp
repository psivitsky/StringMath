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
    precision_(precision), function_(constants, functions), first_rank_operators_(constants), second_rank_operators_(constants),
    constants_(constants), functions_(functions)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The expression analyzer function.
 * \param[in] expressionStr The expression string to analyze.
 * \param[in] calcResultStr The calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::analyze(const QString &expressionStr, QString &calcResultStr) const
{
    QString temp_str_1 = expressionStr;
    QString temp_str_2 = "";

    subexpression_brackets_replacing(temp_str_1);
    subexpression_processing(temp_str_1, temp_str_2);

    first_rank_operators_.interpret(temp_str_2, temp_str_1);
    second_rank_operators_.interpret(temp_str_1, temp_str_2);
    function_.interpret(temp_str_2, temp_str_1);

    rounder();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of replacing subexpressions brackets.\n
 * The function finds and replaces brackets from 'opening_brackets' and 'closing_brackets' with 'base_opening_bracket' and 'base_closing_bracket'.
 * \param[in,out] expressionStr The expression string with brackets to replace.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::subexpression_brackets_replacing(QString &expressionStr) const
{
    foreach(QString opening_bracket, opening_brackets)
        expressionStr = expressionStr.replace(opening_bracket, base_opening_bracket);

    foreach(QString closing_bracket, closing_brackets)
        expressionStr = expressionStr.replace(closing_bracket, base_closing_bracket);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The subexpression processing function.\n
 * This function searches for and calculates subexpressions in a given expression.\n
 * Each subexpression starts with the opening bracket and ends with the closing bracket. The subexpressions searching is based on this fact.\n
 * After the subexpression is found, it is calculated recursively. The subexpression string is replaced by the result of its calculation.
 * \param[in] expressionStrBefore The expression string before processing.
 * \param[out] expressionStrAfter The expression string after processing without subexpressions.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::subexpression_processing(const QString &expressionStrBefore, QString &expressionStrAfter) const
{
    int pos = 0;
    while(true)
    {
        int subexp_begin = subexpression_begin_searching(expressionStrBefore, pos);
        if(subexp_begin == -1)
        {
            expressionStrAfter += expressionStrBefore.mid(pos, expressionStrBefore.length() - pos);
            break;
        }
        else
        {
            int subexp_end = subexpression_end_searching(expressionStrBefore, subexp_begin + 1);
            if(subexp_end == -1)
                throw StringMathError("ExpressionAnalyzer: the closing bracket is missing!");

            //The subexpression recursive analysis...
            QString subexp_str = expressionStrBefore.mid(subexp_begin, subexp_end - subexp_begin + 1);
            QString subexp_str_calc_result_str = "";

            ExpressionAnalyzer subexpression_analyzer(precision_, constants_, functions_);
            subexpression_analyzer.analyze(subexp_str, subexp_str_calc_result_str);

            //The subexpression replacement...
            expressionStrAfter += expressionStrBefore.mid(pos, subexp_begin - pos);
            expressionStrAfter += subexp_str_calc_result_str;
            pos = subexp_end + 1;
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of searching for the beginning of the subexpression.
 * \param[in] expressionStr The expression string.
 * \param[in] findFrom The initial position of the search (non-negative integer value).
 * \return The beginning position of the subexpression (non-negative integer value) or -1 if there is no subexpression.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
int ExpressionAnalyzer::subexpression_begin_searching(const QString &expressionStr, int findFrom) const
{
    int subexp_start = expressionStr.indexOf(base_opening_bracket, findFrom);

    if(subexp_start != -1)
    {
        //The subexpression starting position clarification...
        while(subexp_start > 0)
        {
            if(operators.contains(expressionStr.at(subexp_start - 1)))
                break;
            --subexp_start;
        }
    }

    return subexp_start;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of finding the end of the subexpression.
 * \param[in] expressionStr The expression string.
 * \param[in] findFrom The initial position of the search (non-negative integer value).
 * \return The end of the subexpression (non-negative integer value) or -1 if there is no closing bracket.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
int ExpressionAnalyzer::subexpression_end_searching(const QString &expressionStr, int findFrom) const
{
    int subexp_end = findFrom;

    int subsubexp_number = 0;
    while(subexp_end < expressionStr.length())
    {
        if(expressionStr.at(subexp_end) == base_opening_bracket)
            ++subsubexp_number;
        if(expressionStr.at(subexp_end) == base_closing_bracket)
        {
            if(subsubexp_number == 0)
                break;
            else
                --subsubexp_number;
        }
        ++subexp_end;
    }

    if(subexp_end == expressionStr.length())
        return -1;

    return subexp_end;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The expression calculation result rounder function.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ExpressionAnalyzer::rounder() const
{

}
