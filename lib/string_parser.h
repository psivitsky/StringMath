#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#include    "term_calc.h"

class StringParser
{
public:    
    StringParser();
    //Functions...
    void    parse(const QString &src, QStringList &dst) const;
private:
    StringParser(const StringParser &obj);
    StringParser &operator=(const StringParser &obj);
    //Constants...
    static const int    mid_prec = 32;      //!< \details The precision of intermediate calculations.

    const QString   base_opening_bracket = "(";
    const QString   base_closing_bracket = ")";

    const QString   inf_str = "inf";
    const QString   nan_str = "nan";
    //Containers...
    QStringList opening_brackets = {"[", "{"};
    QStringList closing_brackets = {"]", "}"};

    QStringList operators = {"^", "*", "/", "+", "-"};

    QStringList constants = {"pi"};
    QStringList constants_values = {"3.1415926535897932384626433832795"};
    //Functions...
    void    brackets_replacer(QString &str) const;
    void    subexp_parser(const QString &src, int &srcPos, QStringList &dst) const;
    void    term_checker(const QString &term) const;
};
#endif // STRINGPARSER_H
