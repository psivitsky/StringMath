#include "term_calc.h"

TermCalc::TermCalc()
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation function.
 * \param[in] terms The terms list.
 * \result The calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double TermCalc::calculate(QStringList &terms, int prec) const
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

    return res_rounding(terms.first().toDouble(), prec);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function calculator.
 * \param[in] funcName The function name.
 * \param[in] val The function argument.
 * \result The result of calculations.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
qreal TermCalc::func_calc(const QString &funcName, qreal val) const
{
    if(!functions.contains(funcName))
        throw StringMathError("An unknown function " + funcName + "!");

    int func_index = functions.indexOf(funcName);

    qreal eval_res = val;
    switch(func_index)
    {
    case cosFunc:
        eval_res = qCos(val);
        break;
    case sinFunc:
        eval_res = qSin(val);
        break;
    case tanFunc:
        if(qAbs(qSin(val)) == 1.)
            throw StringMathError("The tangent is infinite!");
        eval_res = qSin(val) / qCos(val);
        break;
    case cotFunc:
        if(qAbs(qCos(val)) == 1.)
            throw StringMathError("The cotangent is infinite!");
        eval_res = qCos(val) / qSin(val);
        break;
    case acosFunc:
        if(qAbs(val) > 1.)
            throw StringMathError("The arccosine subexpression absolute value is greater than 1!");
        eval_res = qAcos(val);
        break;
    case asinFunc:
        if(qAbs(val) > 1.)
            throw StringMathError("The arcsine subexpression absolute value is greater than 1!");
        eval_res = qAsin(val);
        break;
    case atanFunc:
        eval_res = qAtan(val);
        break;
    case acotFunc:
        eval_res = qAsin(1.) - qAtan(val);
        break;
    case logFunc:
        if(val == 0.)
            throw StringMathError("The natural logarithm subexpression value is equal to zero!");
        eval_res = qLn(val);
        break;
    case log10Func:
        if(val == 0.)
            throw StringMathError("The logarithm (base 10) subexpression value is equal to zero!");
        eval_res = qLn(val) / qLn(10.);
        break;
    case log2Func:
        if(val == 0.)
            throw StringMathError("The logarithm (base 2) subexpression value is equal to zero!");
        eval_res = qLn(val) / qLn(2.);
        break;
    case expFunc:
        eval_res = qExp(val);
        break;
    case sqrtFunc:
        if(val < 0.)
            throw StringMathError("The square root subexpression value is negative!");
        eval_res = qSqrt(val);
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
double TermCalc::res_rounding(double resVal, int prec) const
{
    double int_part = static_cast<double>(qFloor(resVal));
    double nonint_part = resVal - qFloor(resVal);

    double prec_dec = qPow(10., prec);
    nonint_part = static_cast<double>(qRound(nonint_part * prec_dec)) / prec_dec;

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
void TermCalc::power(QStringList &terms) const
{
    if((terms.indexOf(pow_op) - 1) < 0)
        throw StringMathError("The left operand of " + pow_op + " doesn't exist!");

    qreal pow = qPow(terms.at(terms.indexOf(pow_op) - 1).toDouble(), terms.at(terms.indexOf(pow_op) + 1).toDouble());
    terms.removeAt(terms.indexOf(pow_op) - 1);
    terms.removeAt(terms.indexOf(pow_op) + 1);
    terms.replace(terms.indexOf(pow_op), QString::number(pow, 'f', mid_prec));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The product calculation function.
 * \param[in,out] terms The terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void TermCalc::product(QStringList &terms) const
{
    if((terms.indexOf(prod_op) - 1) < 0)
        throw StringMathError("Left operand of " + prod_op + " doesn't exist!");

    qreal prod = terms.at(terms.indexOf(prod_op) - 1).toDouble() * terms.at(terms.indexOf(prod_op) + 1).toDouble();
    terms.removeAt(terms.indexOf(prod_op) - 1);
    terms.removeAt(terms.indexOf(prod_op) + 1);
    terms.replace(terms.indexOf(prod_op), QString::number(prod, 'f', mid_prec));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The quotient calculation function.
 * \param[in,out] terms The terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void TermCalc::quotient(QStringList &terms) const
{
    if((terms.indexOf(quot_op) - 1) < 0)
        throw StringMathError("Left operand of " + quot_op + " doesn't exist!");

    if(terms.at(terms.indexOf(quot_op) + 1).toDouble() == 0.)
        throw(StringMathError(terms.at(terms.indexOf(quot_op) - 1) + quot_op + terms.at(terms.indexOf(quot_op) + 1) + " divide by zero!"));

    qreal quot = terms.at(terms.indexOf(quot_op) - 1).toDouble() / terms.at(terms.indexOf(quot_op) + 1).toDouble();
    terms.removeAt(terms.indexOf(quot_op) - 1);
    terms.removeAt(terms.indexOf(quot_op) + 1);
    terms.replace(terms.indexOf(quot_op), QString::number(quot, 'f', mid_prec));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The sum calculation function.
 * \param[in,out] terms The terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void TermCalc::sum(QStringList &terms) const
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
    terms.replace(terms.indexOf(sum_op), QString::number(sum, 'f', mid_prec));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The difference calculation function.
 * \param[in,out] terms The terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void TermCalc::difference(QStringList &terms) const
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
    terms.replace(terms.indexOf(diff_op), QString::number(diff, 'f', mid_prec));
}
