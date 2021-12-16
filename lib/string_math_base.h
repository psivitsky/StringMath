#ifndef STRING_MATH_BASE_H
#define STRING_MATH_BASE_H

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

#endif // STRING_MATH_BASE_H
