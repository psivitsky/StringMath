//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * The mathematical constant
 * \details
 * Class description
 * -----
 * This class defines a mathematical constant by its name and value.\n
 * The name of the constant must consist of three letters.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef STRINGMATHCONSTANT_H
#define STRINGMATHCONSTANT_H

#include    "string_math_base.h"

#include    <QRegExp>

class STRINGMATH_EXPORT StringMathConstant
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
#endif // STRINGMATHCONSTANT_H
