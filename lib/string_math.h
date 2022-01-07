#ifndef STRING_MATH_H
#define STRING_MATH_H
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Expression calculation from QString
 * \details
 * Class description
 * -----
 * The class object performs calculations from a given expression in string format.
 * It parses the input string in terms and tranfers them to the TermCalc object.
 * The calculcation result is given with 'res_prec' accuracy.
 *
 * The input expression can contain subexpresions in bracket of diffrent types ('()', '[]' and '{}').
 * The object can compute functions (see 'functions' list). Their names are taken from MATLAB.
 * The object also supports constants such as 'pi'.
 *
 * If the object finds a syntax error or, for example, a division by zero, it throws an exception of the 'StringMathError' type.
 *
 * Code example
 * -----
 * \code
 * try
 * {
 *     QString exp_str = "6/2*(2+1)";
 *
 *     StringMath obj(3);                               //Calculator with '3' precision.
 *     doubel result = obj.string_process(exp_str);     //The result will be 9.
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

#include    "list_math.h"

class STRINGMATH_EXPORT StringMath
{
public:
    explicit StringMath(int prec = 8);
    //Functions...
    void    set_precision(int prec);
    int     precision() const;

    void    add_constant(const QString &constantName, double constantValue);
    void    remove_constant(const QString &constantName);

    double  string_process(const QString &str);
private:
    StringMath(const StringMath &obj);
    StringMath &operator=(const StringMath &obj);
    //Constants...
    const QString   base_opening_bracket = "(";
    const QString   base_closing_bracket = ")";
    //Containers...
    QStringList opening_brackets = {"[", "{"};
    QStringList closing_brackets = {"]", "}"};

    QStringList operators = {"^", "*", "/", "+", "-"};

    QStringList constants = {"pi"};
    QStringList constants_values = {"3.1415926535897932384626433832795"};
    //Variables...
    int res_prec;       //!< \details The precision of calculation result.
    //Functions...
    void    parse(const QString &src, QStringList &dst) const;    
    void    subexp_parser(const QString &src, int &srcPos, QStringList &dst) const;

    void    term_checker(const QString &term) const;

    void    brackets_replacer(QString &exp) const;
    void    constant_replacer(QString &term) const;
    void    spaces_remover(QString &term) const;
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
