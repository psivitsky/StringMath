#include "string_parser.h"

StringParser::StringParser()
{

}

void StringParser::parse(const QString &src, QStringList &dst) const
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

void StringParser::brackets_replacer(QString &str) const
{
    foreach(QString opening_bracket, opening_brackets)
        str = str.replace(opening_bracket, base_opening_bracket);

    foreach(QString closing_bracket, closing_brackets)
        str = str.replace(closing_bracket, base_closing_bracket);
}

void StringParser::subexp_parser(const QString &src, int &srcPos, QStringList &dst) const
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

void StringParser::term_checker(const QString &term) const
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
