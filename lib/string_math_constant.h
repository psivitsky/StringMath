//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Mathematical constant
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
    //Operators...
    friend bool operator== (const StringMathConstant &obj1, const StringMathConstant &obj2);
    //Functions...
    void    set(const QString &constantName, double constantValue);

    void    set_value(double value);
    double  value() const;

    void            set_name(const QString &constantName);
    const QString   &name() const;
private:
    double  value_;
    QString name_;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The mathematical constant value setter function.
 * \param[in] value The mathematical constant value.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline void StringMathConstant::set_value(double value)
{
    value_ = value;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The mathematical constant name getter function.
 * \return The mathematical constant name.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline const QString &StringMathConstant::name() const
{
    return name_;
}
#endif // STRINGMATHCONSTANT_H
