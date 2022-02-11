//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Second rank algebraic operators interpreter
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
    //Functions...
    void    interpret(const QString &expressionStr, QString &interpretedExpStr) const;
private:
    SROpInterpreter(const SROpInterpreter &obj);
    SROpInterpreter &operator=(const SROpInterpreter &obj);
    //Constants...
    const QString       sum_operator = "+";
    const QString       diff_operator = "-";
    //Functions...
    double  calculate(QString::const_iterator begin, QString::const_iterator end, bool fFirstOperand) const;
};
#endif // SROPINTERPRETER_H
