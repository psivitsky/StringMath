//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Class for a algebraic function in string format for calculations in the StringMath class
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef STRINGMATHFUNCTION_H
#define STRINGMATHFUNCTION_H

#include    "string_math_base.h"

class StringMathFunction
{
public:
    StringMathFunction();
    StringMathFunction(const QString &functionName);
    //Functions...
    void    set_name(const QString &constantName);
    const QString &name() const;
private:
    QString name_;
};

inline const QString &StringMathFunction::name() const
{
    return name_;
}
#endif // STRINGMATHFUNCTION_H
