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
    parse(str, terms);

    TermCalc calc;

    return calc.calculate(terms, res_prec);
}

void StringMath::parse(const QString &src, QStringList &dst) const
{
    QString str_exp = src;
    brackets_replacer(str_exp);

    QString term = "";

    TermCalc calc;

    int str_pos = 0;
    while(str_pos < src.size())
    {
        QChar ch = src.at(str_pos);
        if(ch == base_opening_bracket)
        {
            ++str_pos;

            QStringList subexp_terms;
            subexp_parser(src, str_pos, subexp_terms);
            double subexp_val = calc.calculate(subexp_terms, mid_prec);

            if(!term.isEmpty())
                term = QString::number(calc.func_calc(term, subexp_val), 'f', mid_prec);
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

void StringMath::brackets_replacer(QString &str) const
{
    foreach(QString opening_bracket, opening_brackets)
        str = str.replace(opening_bracket, base_opening_bracket);

    foreach(QString closing_bracket, closing_brackets)
        str = str.replace(closing_bracket, base_closing_bracket);
}

void StringMath::subexp_parser(const QString &src, int &srcPos, QStringList &dst) const
{
    QString term = "";

    TermCalc calc;

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
            double subexp_val = calc.calculate(subexp_terms, mid_prec);

            if(!term.isEmpty())
                term = QString::number(calc.func_calc(term, subexp_val), 'f', mid_prec);
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
