//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Algebraic function
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef STRINGMATHFUNCTION_H
#define STRINGMATHFUNCTION_H

#include    "string_math_base.h"

class STRINGMATH_EXPORT StringMathFunction
{
public:
    StringMathFunction();
    StringMathFunction(const QString &functionName);
    //Operators...
    friend bool operator== (const StringMathFunction &obj1, const StringMathFunction &obj2);
    //Functions...
    void            set_name(const QString &constantName);
    const QString   &name() const;
private:
    QString name_;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function name getter function.
 * \return The algebraic function name.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline const QString &StringMathFunction::name() const
{
    return name_;
}
#endif // STRINGMATHFUNCTION_H
