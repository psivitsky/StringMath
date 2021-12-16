#ifndef TERMCALC_H
#define TERMCALC_H

#include    <qmath.h>

#include    "string_math_base.h"

class TermCalc
{
public:
    TermCalc();
    //Functions...
    double  calculate(QStringList &terms, int prec = 8) const;
    qreal   func_calc(const QString &funcName, qreal val) const;
private:
    TermCalc(const TermCalc &obj);
    TermCalc &operator=(const TermCalc &obj);
    //Constants...
    static const int    mid_prec = 32;      //!< \details The precision of intermediate calculations.

    const QString   pow_op = "^";
    const QString   prod_op = "*";
    const QString   quot_op = "/";
    const QString   sum_op = "+";
    const QString   diff_op = "-";
    //Containers...
    QStringList functions = {"cos", "sin", "tan", "cot",
                             "acos", "asin", "atan", "acot",
                             "log", "log10", "log2", "exp", "sqrt"};
    enum functionsIndexes {cosFunc, sinFunc, tanFunc, cotFunc,
                           acosFunc, asinFunc, atanFunc, acotFunc,
                           logFunc, log10Func, log2Func, expFunc, sqrtFunc};
    //Functions...
    double  res_rounding(double resVal, int prec) const;

    void    power(QStringList &terms) const;
    void    product(QStringList &terms) const;
    void    quotient(QStringList &terms) const;
    void    sum(QStringList &terms) const;
    void    difference(QStringList &terms) const;
};
#endif // TERMCALC_H
