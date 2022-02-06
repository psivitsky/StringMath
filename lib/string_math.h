//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Mathematical expression calculation
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef STRING_MATH_H
#define STRING_MATH_H

#include    "expression_analyzer.h"
#include    "string_math_constant.h"
#include    "string_math_function.h"

class STRINGMATH_EXPORT StringMath
{
public:
    explicit StringMath(int precisionValue = 8);
    //Functions...
    void    set_precision(int precisionValue);
    int     precision() const;

    void    add_constant(const StringMathConstant &newConstant);
    void    replace_constant(const QString &existingConstantName, double newConstantValue);
    void    remove_constant(const StringMathConstant &existingConstant);
    const QVector<StringMathConstant>   &constants() const;

    void    add_function(const StringMathFunction &newFunction);
    void    replace_function(const QString &existingFunctionName);
    void    remove_function(const StringMathFunction &newFunction);
    const QVector<StringMathFunction>   &functions() const;

    void calculate(const QString &strExpression, QString &calcResult);
private:
    StringMath(const StringMath &obj);
    StringMath &operator=(const StringMath &obj);
    //Constants...    
    static const int    min_precision_value = 0;
    static const int    max_precision_value = 16;
    //Containers...
    QVector<StringMathConstant> constants_ = {StringMathConstant("pi", 3.1415926535897932384626433832795),
                                              StringMathConstant("e", 2.7182818284590452353602874713527)};

    QVector<StringMathFunction> functions_ = {StringMathFunction("cos"),
                                              StringMathFunction("sin"),
                                              StringMathFunction("tan"),
                                              StringMathFunction("cot"),
                                              StringMathFunction("acos"),
                                              StringMathFunction("asin"),
                                              StringMathFunction("atan"),
                                              StringMathFunction("acot"),
                                              StringMathFunction("log"),
                                              StringMathFunction("log10"),
                                              StringMathFunction("log2"),
                                              StringMathFunction("exp"),
                                              StringMathFunction("sqrt")};
    //Variables...
    int precision_ = min_precision_value;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation precision getter function.
 * \return The precision of calculation result (an integer value in range from 'min_precision_value' to 'max_precision_value').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline int StringMath::precision() const
{
    return precision_;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation constants getter function.
 * \return The container with constants (StringMathConstant objects).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline const QVector<StringMathConstant> &StringMath::constants() const
{
    return constants_;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The algebraic functions getter function.
 * \return The container with functions (StringMathFunction objects).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline const QVector<StringMathFunction> &StringMath::functions() const
{
    return functions_;
}
#endif // STRING_MATH_H
