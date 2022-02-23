//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Algebraic functions interpreter
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef FUNCINTERPRETER_H
#define FUNCINTERPRETER_H

#include    "string_math_base.h"
#include    "string_math_function.h"

#include    <QVector>

class FuncInterpreter
{
public:
    FuncInterpreter(const QVector<StringMathFunction> &functions);
    //Methods...
    double  interpret(double funcArgument, const QString &funcName) const;
private:
    FuncInterpreter(const FuncInterpreter &obj);
    FuncInterpreter &operator=(const FuncInterpreter &obj);
    //Containers...
    QVector<StringMathFunction> functions_;
    //Methods...
    void    extract_name(QString::const_iterator &begin, QString::const_iterator end, QString &funcName) const;
    double  extract_argument(QString::const_iterator begin, QString::const_iterator end) const;

    void    calculate(const QString &funcName, double funcArgument, QString &calcResultStr) const;
};
#endif // FUNCINTERPRETER_H
