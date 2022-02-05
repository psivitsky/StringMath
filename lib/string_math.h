//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Mathematical expression calculation from QString
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
    explicit StringMath(int resultPrecision = 8);
    //Functions...
    void    set_precision(int resultPrecision);
    int     precision() const;

    void    add_constant(const StringMathConstant &newConstant);
    void    replace_constant(const QString &existingConstantName, double newConstantValue);
    void    remove_constant(const StringMathConstant &existingConstant);
    const QVector<StringMathConstant>   &constants() const;

    double  calculate(const QString &str);
private:
    StringMath(const StringMath &obj);
    StringMath &operator=(const StringMath &obj);
    //Constants...    
    static const int    mid_prec = 16;
    static const int    min_res_prec = 0;
    static const int    max_res_prec = 16;

    const QString   base_opening_bracket = "(";
    const QString   base_closing_bracket = ")";
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
    int precision_;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The calculation precision getter function.
 * \return The precision of calculation result (an integer in range from 'min_res_prec' to 'max_res_prec').
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline int StringMath::precision() const
{
    return precision_;
}

inline const QVector<StringMathConstant> &StringMath::constants() const
{
    return constants_;
}
#endif // STRING_MATH_H
