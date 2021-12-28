#ifndef STRING_MATH_BASE_H
#define STRING_MATH_BASE_H

#include    <QStringList>

namespace StringMathBase
{
    static const int    mid_prec = 16;      //!< \details The precision of intermediate calculations.

    static const int    min_res_prec = 0;
    static const int    max_res_prec = 16;
}

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

#endif // STRING_MATH_BASE_H
