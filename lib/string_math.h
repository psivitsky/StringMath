#ifndef STRING_MATH_H
#define STRING_MATH_H

#include    <qmath.h>
#include    <QString>
#include    <QStringList>

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * StringMath exception error class.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
class StringMathError
{
public:
    StringMathError(const QString &str) : msg(str) {}
    QString msg;
};

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Expression calculation from QString
 * \details
 * Class description
 * -----
 * A class object performs calculations from a given expression in string format.
 * The object analyzes the input string in terms on which it performs calculations.
 * The result is given with 'res_prec' accuracy.\n
 * The input expression can contain subexpresions in bracket of diffrent types ('()', '[]' and '{}').\n
 * The object can compute functions (see 'functions' list). Their names are taken from MATLAB.\n
 * The object also supports constants such as 'pi'.\n
 * If the object finds a syntax error or, for example, a division by zero, it throws an exception of the 'StringMathError' type.\n
 *
 * Code example
 * -----
 * \code
 * QString exp_str = "6/2*(2+1)";    //Expression setter.
 * try
 * {
 *     StringMath calc(3);                              //Calculator with '3' precision.
 *     doubel result = calc.string_process(exp_str);    //The result will be 9.
 * }
 * catch(StringMathError &err)
 * {
 *     //Error handling (use err.msg).
 * }
 * \endcode
 * \warning
 * The calculator do not ignore spaces!
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------

#if defined(STRINGMATH_LIBRARY)
#  define STRINGMATH_EXPORT Q_DECL_EXPORT
#else
#  define STRINGMATH_EXPORT Q_DECL_IMPORT
#endif

class STRINGMATH_EXPORT StringMath
{
public:
    StringMath(int prec = 8);
    //Functions...
    void    set_precision(int prec);
    int     precision() const;

    double  string_process(const QString &str);
private:
    StringMath(const StringMath &obj);
    StringMath &operator=(const StringMath &obj);
    //Constants...
    static const int    mid_prec = 32;      //!< \details The precision of intermediate calculations.
    static const int    min_res_prec = 0;
    static const int    max_res_prec = 16;

    const QString   base_opening_bracket = "(";
    const QString   base_closing_bracket = ")";

    const QString   pow_op = "^";
    const QString   prod_op = "*";
    const QString   quot_op = "/";
    const QString   sum_op = "+";
    const QString   diff_op = "-";

    const QString   inf_str = "inf";
    const QString   nan_str = "nan";
    //Variables...
    int res_prec = min_res_prec;        //!< \details The precision of calculation result.
    //Containers...
    QStringList opening_brackets = {"[", "{"};
    QStringList closing_brackets = {"]", "}"};

    QStringList operators = {"^", "*", "/", "+", "-"};

    QStringList constants = {"pi"};
    QStringList constants_values = {"3.1415926535897932384626433832795"};

    QStringList functions = {"cos", "sin", "tan", "cot",
                             "acos", "asin", "atan", "acot",
                             "log", "log10", "log2", "exp", "sqrt"};
    enum functionsIndexes {cosFunc, sinFunc, tanFunc, cotFunc,
                           acosFunc, asinFunc, atanFunc, acotFunc,
                           logFunc, log10Func, log2Func, expFunc, sqrtFunc};
    //Functions...
    void    brackets_replacer(QString &str) const;

    void    parser(const QString &src, QStringList &dst) const;
    void    subexp_parser(const QString &src, int &srcPos, QStringList &dst) const;

    void    term_checker(const QString &term) const;

    double  calculate(QStringList &terms) const;
    double  res_rounding(double resVal) const;

    void    power(QStringList &terms) const;
    void    product(QStringList &terms) const;
    void    quotient(QStringList &terms) const;
    void    sum(QStringList &terms) const;
    void    difference(QStringList &terms) const;

    qreal   func_calc(const QString &funcName, qreal val) const;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation precision getter.
 * \return The precision of calculation result (an integer in range from 'min_res_prec' to 'max_res_prec').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline int StringMath::precision() const
{
    return res_prec;
}
#endif // STRING_MATH_H
