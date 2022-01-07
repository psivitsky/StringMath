#include "list_math.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The default constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
ListMath::ListMath() : res_prec(StringMathBase::min_res_prec)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] prec The precision of calculation result (an integer in range from 'min_res_prec' to 'max_res_prec').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
ListMath::ListMath(int prec) : res_prec(StringMathBase::min_res_prec)
{
    set_precision(prec);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation precision setter.
 * \param[in] prec The precision of calculation result (an integer in range from 'min_res_prec' to 'max_res_prec').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ListMath::set_precision(int prec)
{
    if(prec < StringMathBase::min_res_prec)
        throw StringMathError("The precision of calculation result is too low!");
    if(prec > StringMathBase::max_res_prec)
        throw StringMathError("The precision of calculation result is too big!");

    res_prec = prec;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation function.
 * \param[in] terms The terms list.
 * \result The calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double ListMath::list_process(QStringList &terms) const
{
    while(terms.contains(pow_op))
        power(terms);

    while(terms.contains(prod_op) || terms.contains(div_op))
    {
        int op_pos = 0;
        while(op_pos < terms.size())
        {
            if((terms.at(op_pos) == prod_op) || (terms.at(op_pos) == div_op))
                break;
            ++op_pos;
        }

        if(terms.at(op_pos) == prod_op)
        {
            product(terms);
            continue;
        }

        if(terms.at(op_pos) == div_op)
        {
            division(terms);
            continue;
        }
    }

    while(terms.contains(sum_op) || terms.contains(diff_op))
    {
        int op_pos = 0;
        while(op_pos < terms.size())
        {
            if((terms.at(op_pos) == sum_op) || (terms.at(op_pos) == diff_op))
                break;
            ++op_pos;
        }

        if(terms.at(op_pos) == sum_op)
        {
            sum(terms);
            continue;
        }

        if(terms.at(op_pos) == diff_op)
        {
            difference(terms);
            continue;
        }
    }

    return res_rounding(terms.first().toDouble(), res_prec);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function calculator.
 * \param[in] funcName The function name.
 * \param[in] val The function argument.
 * \result The result of calculations.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double ListMath::func_calc(const QString &funcName, double funcArg) const
{
    if(!StringMathBase::functions.contains(funcName))
        throw StringMathError("An unknown function " + funcName + "!");

    int func_index = StringMathBase::functions.indexOf(funcName);

    double eval_res = funcArg;
    switch(func_index)
    {
        case StringMathBase::cosFunc:
            eval_res = cos(funcArg);
            break;
        case StringMathBase::sinFunc:
            eval_res = sin(funcArg);
            break;
        case StringMathBase::tanFunc:
            if(qAbs(sin(funcArg)) == 1.)
                throw StringMathError("The tangent is infinite!");
            eval_res = tan(funcArg);
            break;
        case StringMathBase::cotFunc:
            if(qAbs(cos(funcArg)) == 1.)
                throw StringMathError("The cotangent is infinite!");
            eval_res = 1. / tan(funcArg);
            break;
        case StringMathBase::acosFunc:
            if(qAbs(funcArg) > 1.)
                throw StringMathError("The arccosine subexpression absolute value is greater than 1!");
            eval_res = acos(funcArg);
            break;
        case StringMathBase::asinFunc:
            if(qAbs(funcArg) > 1.)
                throw StringMathError("The arcsine subexpression absolute value is greater than 1!");
            eval_res = asin(funcArg);
            break;
        case StringMathBase::atanFunc:
            eval_res = atan(funcArg);
            break;
        case StringMathBase::acotFunc:
            eval_res = atan(1. / funcArg);
            break;
        case StringMathBase::logFunc:
            if(funcArg <= 0.)
                throw StringMathError("The natural logarithm subexpression value is less than or equal to zero!");
            eval_res = log(funcArg);
            break;
        case StringMathBase::log10Func:
            if(funcArg <= 0.)
                throw StringMathError("The logarithm (base 10) subexpression value is less than or equal to zero!");
            eval_res = log10(funcArg);
            break;
        case StringMathBase::log2Func:
            if(funcArg == 0.)
                throw StringMathError("The logarithm (base 2) subexpression value is less than or equal to zero!");
            eval_res = log2(funcArg);
            break;
        case StringMathBase::expFunc:
            eval_res = exp(funcArg);
            break;
        case StringMathBase::sqrtFunc:
            if(funcArg < 0.)
                throw StringMathError("The square root subexpression value is negative!");
            eval_res = sqrt(funcArg);
            break;
        default:
            break;
    }

    res_check(eval_res, funcName + "(" + QString::number(funcArg, 'f', res_prec) + ")");

    return eval_res;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation result check function.\n
 * The function can detect infinite or 'not a number' and throw an exception.
 * \param[in] resVal The calculation result.
 * \param[in] expStr The expression string.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ListMath::res_check(double resVal, const QString &expStr) const
{
    switch(std::fpclassify(resVal))
    {
        case FP_INFINITE:
            throw StringMathError("\"" + expStr + "\" calculation result is infinite!");
            break;
        case FP_NAN:
            throw StringMathError("\"" + expStr + "\" calculation result is not a number!");
            break;
        default:
            break;
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation result rounding function.\n
 * The non-integer part is rounded separately to prevent processing of large numbers.
 * \param[in] resVal The calculation result.
 * \param[in] prec The precision of calculation result
 * \result The rounded calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double ListMath::res_rounding(double resVal, int prec) const
{
    double int_part = static_cast<double>(floor(resVal));
    double nonint_part = resVal - floor(resVal);

    double prec_dec = pow(10., prec);
    nonint_part = static_cast<double>(floor(nonint_part * prec_dec + 0.5)) / prec_dec;

    return int_part + nonint_part;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The power calculation function.\n
 * This function calculates the power of two operands.\n
 * After that, it replaces them with the calculation result.
 * \param[in,out] terms The terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ListMath::power(QStringList &terms) const
{
    if((terms.indexOf(pow_op) - 1) < 0)
        throw StringMathError("The left operand of " + pow_op + " doesn't exist!");

    if(terms.at(terms.indexOf(pow_op) - 1).toDouble() == 0.)
        throw(StringMathError(terms.at(terms.indexOf(pow_op) - 1) + pow_op + terms.at(terms.indexOf(pow_op) + 1) + " base is equal to zero!"));

    double res = pow(terms.at(terms.indexOf(pow_op) - 1).toDouble(), terms.at(terms.indexOf(pow_op) + 1).toDouble());

    res_check(res, terms.at(terms.indexOf(pow_op) - 1) + pow_op + terms.at(terms.indexOf(pow_op) + 1));

    terms.removeAt(terms.indexOf(pow_op) - 1);
    terms.removeAt(terms.indexOf(pow_op) + 1);
    terms.replace(terms.indexOf(pow_op), QString::number(res, 'f', StringMathBase::mid_prec));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The product calculation function.
 * \param[in,out] terms The terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ListMath::product(QStringList &terms) const
{
    if((terms.indexOf(prod_op) - 1) < 0)
        throw StringMathError("Left operand of " + prod_op + " doesn't exist!");

    double prod = terms.at(terms.indexOf(prod_op) - 1).toDouble() * terms.at(terms.indexOf(prod_op) + 1).toDouble();

    res_check(prod, terms.at(terms.indexOf(prod_op) - 1) + prod_op + terms.at(terms.indexOf(prod_op) + 1));

    terms.removeAt(terms.indexOf(prod_op) - 1);
    terms.removeAt(terms.indexOf(prod_op) + 1);
    terms.replace(terms.indexOf(prod_op), QString::number(prod, 'f', StringMathBase::mid_prec));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The division function.
 * \param[in,out] terms The terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ListMath::division(QStringList &terms) const
{
    if((terms.indexOf(div_op) - 1) < 0)
        throw StringMathError("Left operand of " + div_op + " doesn't exist!");

    if(terms.at(terms.indexOf(div_op) + 1).toDouble() == 0.)
        throw(StringMathError(terms.at(terms.indexOf(div_op) - 1) + div_op + terms.at(terms.indexOf(div_op) + 1) + " divide by zero!"));

    double quot = terms.at(terms.indexOf(div_op) - 1).toDouble() / terms.at(terms.indexOf(div_op) + 1).toDouble();

    res_check(quot, terms.at(terms.indexOf(div_op) - 1) + div_op + terms.at(terms.indexOf(div_op) + 1));

    terms.removeAt(terms.indexOf(div_op) - 1);
    terms.removeAt(terms.indexOf(div_op) + 1);
    terms.replace(terms.indexOf(div_op), QString::number(quot, 'f', StringMathBase::mid_prec));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The sum calculation function.
 * \param[in,out] terms The terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ListMath::sum(QStringList &terms) const
{
    double sum = 0;
    if((terms.indexOf(sum_op) - 1) < 0)
        sum = terms.at(terms.indexOf(sum_op) + 1).toDouble();
    else
    {
        sum = terms.at(terms.indexOf(sum_op) - 1).toDouble() + terms.at(terms.indexOf(sum_op) + 1).toDouble();

        res_check(sum, terms.at(terms.indexOf(sum_op) - 1) + sum_op + terms.at(terms.indexOf(sum_op) + 1));

        terms.removeAt(terms.indexOf(sum_op) - 1);
    }

    terms.removeAt(terms.indexOf(sum_op) + 1);
    terms.replace(terms.indexOf(sum_op), QString::number(sum, 'f', StringMathBase::mid_prec));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The difference calculation function.
 * \param[in,out] terms The terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ListMath::difference(QStringList &terms) const
{
    double diff = 0;
    if((terms.indexOf(diff_op) - 1) < 0)
        diff = - terms.at(terms.indexOf(diff_op) + 1).toDouble();
    else
    {
        diff = terms.at(terms.indexOf(diff_op) - 1).toDouble() - terms.at(terms.indexOf(diff_op) + 1).toDouble();

        res_check(diff, terms.at(terms.indexOf(diff_op) - 1) + diff_op + terms.at(terms.indexOf(diff_op) + 1));

        terms.removeAt(terms.indexOf(diff_op) - 1);
    }

    terms.removeAt(terms.indexOf(diff_op) + 1);
    terms.replace(terms.indexOf(diff_op), QString::number(diff, 'f', StringMathBase::mid_prec));
}
