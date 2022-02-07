//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * The algebraic function
 * \details
 * Class description
 * -----
 * This class defines an algebraic function by its name and implementation.\n
 * The name of the function must consist of five letters or numbers.\n
 * The implementation of the function must receive a double value as an argument and return a double value as a result of the calculation.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef STRINGMATHFUNCTION_H
#define STRINGMATHFUNCTION_H

#include    "string_math_base.h"

#include    <QRegExp>

#include    <functional>

class STRINGMATH_EXPORT StringMathFunction
{
public:
    StringMathFunction();
    StringMathFunction(const QString &functionName, std::function<double (double)> function);
    //Operators...
    friend bool operator== (const StringMathFunction &obj1, const StringMathFunction &obj2);
    //Functions...
    void    set(const QString &functionName, std::function<double (double)> function);

    void            set_name(const QString &functionName);
    const QString   &name() const;

    void                            set_function(std::function<double (double)> function);
    std::function<double (double)>  function() const;

    double  calculate(double argument) const;
private:
    QString                         name_;
    std::function<double(double)>   function_;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic function implementation setter.
 * \param[in] function The algebraic function implementation.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline void StringMathFunction::set_function(std::function<double (double)> function)
{
    function_ = function;
}
#endif // STRINGMATHFUNCTION_H
