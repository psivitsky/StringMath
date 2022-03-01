//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Algebraic function
 * \details
 * Class description
 * -----
 * This class defines an algebraic function by its name and implementation.
 *
 * The name of the function must consist of five letters or numbers.
 * However, the function name must contain at least one letter.
 *
 * The implementation of the function must receive a double value as an argument
 * and return a double value as a result of the calculation.
 *
 * If the class object finds an error it throws an exception of the
 * 'StringMathError' type.
 *
 * Code example
 * -----
 * \code
 *
 * double my_sqr(double arg) { return arg * arg; };
 *
 * StringMath calculator;
 *
 * try
 * {
 *     calculator.add_function(StringMathConstant("sqr", my_sqr));
 *     calculator.calculate("sqr(2)");
 *     // The result will be "4".
 * }
 * catch(StringMathError &err)
 * {
 *     // Error handling (use err.what()).
 * }
 * \endcode
 *
 * \warning
 * If an object has an empty name, its implementation cannot be obtained.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef STRINGMATHFUNCTION_H
#define STRINGMATHFUNCTION_H

#include "string_math_base.h"

#include <QRegExp>

#include <functional>

class STRINGMATH_EXPORT StringMathFunction
{
public:
    StringMathFunction();
    StringMathFunction(const QString&                functionName,
                       std::function<double(double)> function);
    StringMathFunction(const StringMathFunction& obj) = default;
    StringMathFunction& operator=(const StringMathFunction& obj) = default;
    ~StringMathFunction() = default;
    // Functions...
    friend bool operator==(const StringMathFunction& obj1,
                           const StringMathFunction& obj2);

    void set(const QString&                functionName,
             std::function<double(double)> function);

    void           set_name(const QString& functionName);
    const QString& name() const;

    void set_function(std::function<double(double)> function);
    std::function<double(double)> function() const;

    double calculate(double argument) const;

private:
    // Variables...
    QString                       name_;
    std::function<double(double)> function_;
};
#endif // STRINGMATHFUNCTION_H
