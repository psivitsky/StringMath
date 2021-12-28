//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Expression calculation from QStringList
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
 *     double func_arg = 10.;
 *     QString func_name = "log10";
 *
 *     ListMath obj(1);                                 //Calculator with '1' precision.
 *     doubel result = obj.list_process(exp_terms);     //The result will be 9.0
 *     result = obj.func_calc(func_name, func_arg);     //The result will be 1.0
 * }
 * catch(StringMathError &err)
 * {
 *     //Error handling (use err.msg).
 * }
 * \endcode
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef LISTMATH_H
#define LISTMATH_H

#if defined(STRINGMATH_LIBRARY)
#  define STRINGMATH_EXPORT Q_DECL_EXPORT
#else
#  define STRINGMATH_EXPORT Q_DECL_IMPORT
#endif

#include    <cmath>

#include    "string_math_base.h"

class ListMath
{
public:
    ListMath();
    explicit ListMath(int prec);
    //Functions...
    void    set_precision(int prec);
    int     precision() const;

    double  list_process(QStringList &terms) const;
    double  func_calc(const QString &funcName, double funcArg) const;
private:
    ListMath(const ListMath &obj);
    ListMath &operator=(const ListMath &obj);
    //Constants...
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
inline int ListMath::precision() const
{
    return res_prec;
}
#endif // LISTMATH_H
