//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * First rang algebraic operators interpreter
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef FROPINTERPRETER_H
#define FROPINTERPRETER_H

#include    "op_interpreter.h"

class FROpInterpreter : public OpInterpreter
{
public:
    FROpInterpreter(const QVector<StringMathConstant> &constants);

    void    interpret(const QString &expressionStr, QString &interpretedExpStr) const;
private:
    FROpInterpreter(const FROpInterpreter &obj);
    FROpInterpreter &operator=(const FROpInterpreter &obj);
};
#endif // FROPINTERPRETER_H
