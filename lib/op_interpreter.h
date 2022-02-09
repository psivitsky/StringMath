//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Algebraic operators interpreter
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef OPINTERPRETER_H
#define OPINTERPRETER_H

#include    <QVector>

#include    "string_math_base.h"
#include    "string_math_constant.h"

class OpInterpreter
{
public:
    virtual void    interpret(const QString &expressionStr, QString &interpretedExpStr) const = 0;
protected:
    OpInterpreter(const QVector<StringMathConstant> &constants);
    //Functions...
    void    replace_constant();
    void    operand_checker();
private:
    OpInterpreter(const OpInterpreter &obj);
    OpInterpreter &operator=(const OpInterpreter &obj);
    //Containers...
    QVector<StringMathConstant> constants_;
};
#endif // OPINTERPRETER_H
