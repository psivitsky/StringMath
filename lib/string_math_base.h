#ifndef STRING_MATH_BASE_H
#define STRING_MATH_BASE_H

#include    <QString>
#include    <QtCore/qglobal.h>

#if defined(STRINGMATH_LIBRARY)
#  define STRINGMATH_EXPORT Q_DECL_EXPORT
#else
#  define STRINGMATH_EXPORT Q_DECL_IMPORT
#endif

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * StringMath exception error class.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
class StringMathError
{
public:
    StringMathError(const QString &str) : msg(str) {}
    const QString &what() { return msg; }
private:
    QString msg;
};

#endif // STRING_MATH_BASE_H
