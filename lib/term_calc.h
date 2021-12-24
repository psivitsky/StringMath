//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Expression calculation from terms
 * \details
 * Class description
 * -----
 * The class object performs calculations from the specified expression in the list format.
 * It can also compute a given function from the specified argument. Their names are taken from MATLAB.
 * The calculcation result is given with 'res_prec' accuracy.
 *
 * If the object finds a syntax error or, for example, a division by zero, it throws an exception of the 'StringMathError' type.
 *
 * Code example
 * -----
 * \code
 * try
 * {
 *     QStringList exp_terms = {"6", "/", "2", "*", "(", "2", "+", "1")};
 *
 *     qreal func_arg = 10.;
 *     QString func_name = "log10";
 *
 *     TermCalc calc(1);                                //Calculator with '1' precision.
 *     doubel result = calc.calculate(exp_terms);       //The result will be 9.0
 *     result = calc.func_calc(func_name, func_arg);    //The result will be 1.0
 * }
 * catch(StringMathError &err)
 * {
 *     //Error handling (use err.msg).
 * }
 * \endcode
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef TERMCALC_H
#define TERMCALC_H

#if defined(STRINGMATH_LIBRARY)
#  define STRINGMATH_EXPORT Q_DECL_EXPORT
#else
#  define STRINGMATH_EXPORT Q_DECL_IMPORT
#endif

#include    <qmath.h>

#include    "string_math_base.h"

class STRINGMATH_EXPORT TermCalc
{
public:
    TermCalc();
    explicit TermCalc(int prec);
    //Functions...
    void    set_precision(int prec);
    int     precision() const;

    double  calculate(QStringList &terms) const;
    qreal   func_calc(const QString &funcName, qreal funcArg) const;
private:
    TermCalc(const TermCalc &obj);
    TermCalc &operator=(const TermCalc &obj);
    //Constants...
    static const int    mid_prec = 32;      //!< \details The precision of intermediate calculations.
    static const int    min_res_prec = 0;
    static const int    max_res_prec = 32;

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
    //Variables...
    int res_prec;       //!< \details The precision of calculation result.
    //Functions...
    double  res_rounding(double resVal, int prec) const;

    void    power(QStringList &terms) const;
    void    product(QStringList &terms) const;
    void    quotient(QStringList &terms) const;
    void    sum(QStringList &terms) const;
    void    difference(QStringList &terms) const;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation precision getter.
 * \return The precision of calculation result (an integer in range from 'min_res_prec' to 'max_res_prec').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline int TermCalc::precision() const
{
    return res_prec;
}
#endif // TERMCALC_H
