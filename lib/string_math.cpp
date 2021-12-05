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
    QString str_exp = str;
    brackets_replacer(str_exp);

    QStringList terms;
    parser(str_exp, terms);

    double res_val = calculate(terms);

    return res_rounding(res_val);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of replacing brackets.\n
 * The function finds and replaces brackets from 'opening_brackets' and 'closing_brackets' with 'base_opening_bracket' and 'base_closing_bracket'.
 * \param[in,out] str Expression of QString type.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::brackets_replacer(QString &str) const
{
    foreach(QString opening_bracket, opening_brackets)
        str = str.replace(opening_bracket, base_opening_bracket);

    foreach(QString closing_bracket, closing_brackets)
        str = str.replace(closing_bracket, base_closing_bracket);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The parser function.
 * \param[in] src Expression of QString type.
 * \param[out] dst Terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::parser(const QString &src, QStringList &dst) const
{
    QString term = "";

    int str_pos = 0;
    while(str_pos < src.size())
    {
        QChar ch = src.at(str_pos);
        if(ch == base_opening_bracket)
        {
            ++str_pos;

            QStringList subexp_terms;
            subexp_parser(src, str_pos, subexp_terms);
            double subexp_val = calculate(subexp_terms);

            if(!term.isEmpty())
                term = QString::number(func_calc(term, subexp_val), 'f', mid_prec);
            else
                term = QString::number(subexp_val, 'f', mid_prec);

        }
        else if(operators.contains(ch))
        {
            if(str_pos != 0)
            {
                if(constants.contains(term))
                    term = constants_values.at(constants.indexOf(term));
                else
                    term_checker(term);
                dst.push_back(term);
            }
            dst.push_back(ch);

            term.clear();
        }
        else
            term += ch;

        ++str_pos;
    }

    if(constants.contains(term))
        term = constants_values.at(constants.indexOf(term));
    else
        term_checker(term);
    dst.push_back(term);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The subexpression parser function.\n
 * This function is similar to 'parser' function, but it has some features.
 * \param[in] src Expression of QString type.
 * \param[in] srcPos The position of subexpression in 'src'.
 * \param[out] dst Subexpression terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::subexp_parser(const QString &src, int &srcPos, QStringList &dst) const
{
    QString term = "";

    if(src.at(srcPos) == base_closing_bracket)
        throw(StringMathError("There is no subexpression between brackets!"));

    int start_pos = srcPos;
    while(srcPos < src.size())
    {
        QChar ch = src.at(srcPos);
        if(ch == base_opening_bracket)
        {
            ++srcPos;

            QStringList subexp_terms;
            subexp_parser(src, srcPos, subexp_terms);
            double subexp_val = calculate(subexp_terms);

            if(!term.isEmpty())
                term = QString::number(func_calc(term, subexp_val), 'f', mid_prec);
            else
                term = QString::number(subexp_val, 'f', mid_prec);
        }
        else if(ch == base_closing_bracket)
        {
            if(constants.contains(term))
                term = constants_values.at(constants.indexOf(term));
            else
                term_checker(term);
            dst.push_back(term);

            return;
        }
        else if(operators.contains(ch))
        {
            if(srcPos != start_pos)
            {
                if(constants.contains(term))
                    term = constants_values.at(constants.indexOf(term));
                else
                    term_checker(term);
                dst.push_back(term);
            }
            dst.push_back(ch);

            term.clear();
        }
        else
            term += ch;

        ++srcPos;
    }

    throw StringMathError("The subexpression does not contain closing bracket!");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The term checker function.\n
 * If the function finds any error, it throws an exception.
 * \param[in] term The checking term.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::term_checker(const QString &term) const
{
    if(term.isEmpty())
        throw StringMathError("The operand is empty!");

    if(term == inf_str)
        throw StringMathError("The operand is infinite!");

    if(term == nan_str)
        throw StringMathError("The operand is not a number!");

    if(!term.contains(QRegExp("^\\d+$")) &&                 //A number like '11'.
            !term.contains(QRegExp("^\\d+.$")) &&           //A number like '11.'.
            !term.contains(QRegExp("^-\\d+.$")) &&          //A number like '-11.'.
            !term.contains(QRegExp("^\\d+.\\d+$")) &&       //A number like '11.11'.
            !term.contains(QRegExp("^-\\d+.\\d+$")))        //A number like '-11.11'.
        throw StringMathError("The operand \"" + term + "\" contains invalid symbols!");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation function.
 * \param[in] terms The terms list.
 * \result The calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double StringMath::calculate(QStringList &terms) const
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

    return terms.first().toDouble();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation result rounding function.
 * \param[in] resVal The calculation result.
 * \result The rounded calculation result.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double StringMath::res_rounding(double resVal) const
{
    double int_part = static_cast<double>(qFloor(resVal));
    double nonint_part = resVal - qFloor(resVal);

    double prec_dec = qPow(10., res_prec);
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
void StringMath::power(QStringList &terms) const
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
void StringMath::product(QStringList &terms) const
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
void StringMath::quotient(QStringList &terms) const
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
void StringMath::sum(QStringList &terms) const
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
void StringMath::difference(QStringList &terms) const
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
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function calculator.
 * \param[in] funcName The function name.
 * \param[in] val The function argument.
 * \result The result of calculations.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
qreal StringMath::func_calc(const QString &funcName, qreal val) const
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
