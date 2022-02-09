//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Second rang algebraic operators interpreter
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef SROPINTERPRETER_H
#define SROPINTERPRETER_H

#include    "op_interpreter.h"

class SROpInterpreter : public OpInterpreter
{
public:
    SROpInterpreter(const QVector<StringMathConstant> &constants);

    void    interpret(const QString &expressionStr, QString &interpretedExpStr) const;
private:
    SROpInterpreter(const SROpInterpreter &obj);
    SROpInterpreter &operator=(const SROpInterpreter &obj);
    //Functions...
    double  calculate(QString::const_iterator begin, QString::const_iterator end) const;
};
#endif // SROPINTERPRETER_H
