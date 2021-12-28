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

    while(terms.contains(prod_op) || terms.contains(quot_op))
    {
        int op_pos = 0;
        while(op_pos < terms.size())
        {
            if((terms.at(op_pos) == prod_op) || (terms.at(op_pos) == quot_op))
                break;
            ++op_pos;
        }

        if(terms.at(op_pos) == prod_op)
        {
            product(terms);
            continue;
        }

        if(terms.at(op_pos) == quot_op)
        {
            quotient(terms);
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
qreal ListMath::func_calc(const QString &funcName, qreal funcArg) const
{
    if(!functions.contains(funcName))
        throw StringMathError("An unknown function " + funcName + "!");

    int func_index = functions.indexOf(funcName);

    qreal eval_res = funcArg;
    switch(func_index)
    {
    case cosFunc:
        eval_res = qCos(funcArg);
        break;
    case sinFunc:
        eval_res = qSin(funcArg);
        break;
    case tanFunc:
        if(qAbs(qSin(funcArg)) == 1.)
            throw StringMathError("The tangent is infinite!");
        eval_res = qSin(funcArg) / qCos(funcArg);
        break;
    case cotFunc:
        if(qAbs(qCos(funcArg)) == 1.)
            throw StringMathError("The cotangent is infinite!");
        eval_res = qCos(funcArg) / qSin(funcArg);
        break;
    case acosFunc:
        if(qAbs(funcArg) > 1.)
            throw StringMathError("The arccosine subexpression absolute value is greater than 1!");
        eval_res = qAcos(funcArg);
        break;
    case asinFunc:
        if(qAbs(funcArg) > 1.)
            throw StringMathError("The arcsine subexpression absolute value is greater than 1!");
        eval_res = qAsin(funcArg);
        break;
    case atanFunc:
        eval_res = qAtan(funcArg);
        break;
    case acotFunc:
        eval_res = qAsin(1.) - qAtan(funcArg);
        break;
    case logFunc:
        if(funcArg == 0.)
            throw StringMathError("The natural logarithm subexpression value is equal to zero!");
        eval_res = qLn(funcArg);
        break;
    case log10Func:
        if(funcArg == 0.)
            throw StringMathError("The logarithm (base 10) subexpression value is equal to zero!");
        eval_res = qLn(funcArg) / qLn(10.);
        break;
    case log2Func:
        if(funcArg == 0.)
            throw StringMathError("The logarithm (base 2) subexpression value is equal to zero!");
        eval_res = qLn(funcArg) / qLn(2.);
        break;
    case expFunc:
        eval_res = qExp(funcArg);
        break;
    case sqrtFunc:
        if(funcArg < 0.)
            throw StringMathError("The square root subexpression value is negative!");
        eval_res = qSqrt(funcArg);
        break;
    default:
        break;
    }

    return eval_res;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation result rounding function.
 * \param[in] resVal The calculation result.
 * \param[in] prec The precision of calculation result
 * \result The rounded calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double ListMath::res_rounding(double resVal, int prec) const
{
    double int_part = static_cast<double>(qFloor(resVal));
    double nonint_part = resVal - qFloor(resVal);

    double prec_dec = qPow(10., prec);
    nonint_part = static_cast<double>(qRound64(nonint_part * prec_dec)) / prec_dec;

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

    qreal pow = qPow(terms.at(terms.indexOf(pow_op) - 1).toDouble(), terms.at(terms.indexOf(pow_op) + 1).toDouble());
    terms.removeAt(terms.indexOf(pow_op) - 1);
    terms.removeAt(terms.indexOf(pow_op) + 1);
    terms.replace(terms.indexOf(pow_op), QString::number(pow, 'f', StringMathBase::mid_prec));
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

    qreal prod = terms.at(terms.indexOf(prod_op) - 1).toDouble() * terms.at(terms.indexOf(prod_op) + 1).toDouble();
    terms.removeAt(terms.indexOf(prod_op) - 1);
    terms.removeAt(terms.indexOf(prod_op) + 1);
    terms.replace(terms.indexOf(prod_op), QString::number(prod, 'f', StringMathBase::mid_prec));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The quotient calculation function.
 * \param[in,out] terms The terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ListMath::quotient(QStringList &terms) const
{
    if((terms.indexOf(quot_op) - 1) < 0)
        throw StringMathError("Left operand of " + quot_op + " doesn't exist!");

    if(terms.at(terms.indexOf(quot_op) + 1).toDouble() == 0.)
        throw(StringMathError(terms.at(terms.indexOf(quot_op) - 1) + quot_op + terms.at(terms.indexOf(quot_op) + 1) + " divide by zero!"));

    qreal quot = terms.at(terms.indexOf(quot_op) - 1).toDouble() / terms.at(terms.indexOf(quot_op) + 1).toDouble();
    terms.removeAt(terms.indexOf(quot_op) - 1);
    terms.removeAt(terms.indexOf(quot_op) + 1);
    terms.replace(terms.indexOf(quot_op), QString::number(quot, 'f', StringMathBase::mid_prec));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The sum calculation function.
 * \param[in,out] terms The terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ListMath::sum(QStringList &terms) const
{
    qreal sum = 0;
    if((terms.indexOf(sum_op) - 1) < 0)
        sum = terms.at(terms.indexOf(sum_op) + 1).toDouble();
    else
    {
        sum = terms.at(terms.indexOf(sum_op) - 1).toDouble() + terms.at(terms.indexOf(sum_op) + 1).toDouble();
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
    qreal diff = 0;
    if((terms.indexOf(diff_op) - 1) < 0)
        diff = - terms.at(terms.indexOf(diff_op) + 1).toDouble();
    else
    {
        diff = terms.at(terms.indexOf(diff_op) - 1).toDouble() - terms.at(terms.indexOf(diff_op) + 1).toDouble();
        terms.removeAt(terms.indexOf(diff_op) - 1);
    }
    terms.removeAt(terms.indexOf(diff_op) + 1);
    terms.replace(terms.indexOf(diff_op), QString::number(diff, 'f', StringMathBase::mid_prec));
}
