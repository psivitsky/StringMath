#include "string_math_constant.h"

StringMathConstant::StringMathConstant() : value_(0.), name_("")
{

}

StringMathConstant::StringMathConstant(const QString &constantName, double constantValue) : value_(0.), name_("")
{
    set(constantName, constantValue);
}

bool &StringMathConstant::operator==(const StringMathConstant &obj)
{

}

void StringMathConstant::set(const QString &constantName, double constantValue)
{
    set_name(constantName);
    set_value(constantValue);
}

double StringMathConstant::value() const
{
    if(name_.isEmpty())
        throw StringMathError("StringMathConstant: the constant name is empty!");

    return value_;
}

void StringMathConstant::set_name(const QString &constantName)
{
    QRegExp checker("^\\w{1,3}$");
    if(!checker.exactMatch(constantName))
        throw StringMathError("StringMathConstant: invalid constant name!");

    name_ = constantName;
}
