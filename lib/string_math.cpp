#include "string_math.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The default constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMath::StringMath() : res_prec(StringMathBase::min_res_prec)
{

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] prec The precision of calculation result (an integer in range from 'min_res_prec' to 'max_res_prec').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
StringMath::StringMath(int prec) : res_prec(StringMathBase::min_res_prec)
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
    if(prec < StringMathBase::min_res_prec)
        throw StringMathError("The precision of calculation result is too low!");
    if(prec > StringMathBase::max_res_prec)
        throw StringMathError("The precision of calculation result is too big!");

    res_prec = prec;    
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of calculating the expression.
 * \param[in] str Input expression of QString type.
 * \return The calculation result - a double value with 'res_prec' number of characters after the decimal point.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
double StringMath::string_process(const QString &str)
{
    QStringList terms;
    parse(str, terms);

    ListMath obj(res_prec);

    return obj.list_process(terms);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The parser function.
 * \param[in] src Expression of QString type.
 * \param[out] dst Terms list.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
void StringMath::parse(const QString &src, QStringList &dst) const
{
    QString str_exp = src;
    brackets_replacer(str_exp);

    QString term = "";

    ListMath obj(StringMathBase::mid_prec);

    int str_pos = 0;
    while(str_pos < str_exp.size())
    {
        QChar ch = str_exp.at(str_pos);
        if(ch == base_opening_bracket)
        {
            ++str_pos;

            QStringList subexp_terms;
            subexp_parser(str_exp, str_pos, subexp_terms);
            double subexp_val = obj.list_process(subexp_terms);

            if(!term.isEmpty())
                term = QString::number(obj.func_calc(term, subexp_val), 'f', StringMathBase::mid_prec);
            else
                term = QString::number(subexp_val, 'f', StringMathBase::mid_prec);

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

    ListMath obj(StringMathBase::mid_prec);

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
            double subexp_val = obj.list_process(subexp_terms);

            if(!term.isEmpty())
                term = QString::number(obj.func_calc(term, subexp_val), 'f', StringMathBase::mid_prec);
            else
                term = QString::number(subexp_val, 'f', StringMathBase::mid_prec);
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
