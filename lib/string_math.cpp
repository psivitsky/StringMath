#include "string_math.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] prec The precision of calculation result (an integer in range from 'min_res_prec' to 'max_res_prec').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMath::StringMath(int prec)
{
    set_precision(prec);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation precision setter.
 * \param[in] prec The precision of calculation result (an integer in range from 'min_res_prec' to 'max_res_prec').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::set_precision(int prec)
{
    res_prec = prec;

    if(res_prec < min_res_prec)
        throw StringMathError("The precision of calculation result is too low!");
    if(res_prec > max_res_prec)
        throw StringMathError("The precision of calculation result is too big!");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of calculating the expression.
 * \param[in] str Input expression of QString type.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double StringMath::string_process(const QString &str)
{
    QStringList terms;

    StringParser parser;
    parser.parse(str, terms);

    TermCalc calc;

    return calc.calculate(terms, res_prec);
}
