#ifndef STRING_MATH_H
#define STRING_MATH_H
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

#include    "string_parser.h"

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
    //Variables...
    int res_prec = min_res_prec;        //!< \details The precision of calculation result.
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
