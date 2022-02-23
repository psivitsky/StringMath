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

#include    "string_math_base.h"

#include    <QVector>

class SROpInterpreter
{
public:
    SROpInterpreter();
    //Functions...
    double  interpret(const QVector<StringMathSymbol> &symbols) const;
private:
    SROpInterpreter(const SROpInterpreter &obj);
    SROpInterpreter &operator=(const SROpInterpreter &obj);
};
#endif // SROPINTERPRETER_H
