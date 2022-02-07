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

#include    "op_interpreter.h"

#include    <QVector>

#include    "string_math_function.h"

class FuncInterpreter : public OpInterpreter
{
public:
    FuncInterpreter(const QVector<StringMathFunction> &functions);

    void    interpret(QString &strExpression) const;
private:
    FuncInterpreter(const FuncInterpreter &obj);
    FuncInterpreter &operator=(const FuncInterpreter &obj);
    //Containers...
    QVector<StringMathFunction> functions_;
    //Methods...
    void    extract_name(const QString &strExpression, QString &funcName) const;
    void    check_name(const QString &funcName) const;

    double  extract_argument(const QString &strExpression) const;
};
#endif // FUNCINTERPRETER_H
