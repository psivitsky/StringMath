//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Class for a mathematical constant in string format for calculations in the StringMath class
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef STRINGMATHCONSTANT_H
#define STRINGMATHCONSTANT_H

#include    "string_math_base.h"

#include    <QRegExp>

class StringMathConstant
{
public:
    StringMathConstant();
    StringMathConstant(const QString &constantName, double constantValue);
    //Functions...
    void    set(const QString &constantName, double constantValue);

    void    set_value(double value);
    double  value() const;

    void    set_name(const QString &constantName);
    const QString &name() const;
private:
    double  value_;
    QString name_;
};

inline void StringMathConstant::set_value(double value)
{
    value_ = value;
}

inline const QString &StringMathConstant::name() const
{
    return name_;
}
#endif // STRINGMATHCONSTANT_H
