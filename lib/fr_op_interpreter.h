//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * First rank algebraic operators interpreter
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef FROPINTERPRETER_H
#define FROPINTERPRETER_H

#include    "op_interpreter.h"

#include    <QStringList>

class FROpInterpreter : public OpInterpreter
{
public:
    FROpInterpreter(const QVector<StringMathConstant> &constants);
    //Functions...
    void    interpret(const QString &expressionStr, QString &interpretedExpStr) const;
private:
    FROpInterpreter(const FROpInterpreter &obj);
    FROpInterpreter &operator=(const FROpInterpreter &obj);
    //Constants...
    const QString       mult_operator = "*";
    const QString       div_operator = "/";

    const QStringList   first_rank_operators = {"*", "/"};
    const QStringList   second_rank_operators = {"+", "-"};
    //Functions...
    void    calculate(QString::const_iterator &begin, QString::const_iterator end, QString &leftOperand) const;
};
#endif // FROPINTERPRETER_H
