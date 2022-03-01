//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Mathematical constant
 * \details
 * Class description
 * -----
 * This class defines a mathematical constant by its name and value.
 *
 * The name of the constant must consist of three letters or numbers.
 * However, the constant name must contain at least one letter.
 *
 * If the class object finds an error it throws an exception of the
 * 'StringMathError' type.
 *
 * Code example
 * -----
 * \code
 *
 * StringMath calculator;
 *
 * try
 * {
 *     calculator.add_constant(StringMathConstant("2PI", 6.28));
 *     calculator.calculate("2PI");
 *     // The result will be "6.28".
 * }
 * catch(StringMathError &err)
 * {
 *     // Error handling (use err.what()).
 * }
 * \endcode
 *
 * \warning
 * If an object has an empty name, its value cannot be obtained.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef STRINGMATHCONSTANT_H
#define STRINGMATHCONSTANT_H

#include "string_math_base.h"

#include <QRegExp>

class STRINGMATH_EXPORT StringMathConstant
{
public:
    StringMathConstant();
    StringMathConstant(const QString& constantName, double constantValue);
    StringMathConstant(const StringMathConstant& obj) = default;
    StringMathConstant& operator=(const StringMathConstant& obj) = default;
    ~StringMathConstant() = default;
    // Functions...
    friend bool operator==(const StringMathConstant& obj1,
                           const StringMathConstant& obj2);

    void set(const QString& constantName, double constantValue);

    void   set_value(double value);
    double value() const;

    void           set_name(const QString& constantName);
    const QString& name() const;

private:
    // Variables...
    double  value_;
    QString name_;
};
#endif // STRINGMATHCONSTANT_H
