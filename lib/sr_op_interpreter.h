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

#include "expression_checker.h"

class SROpInterpreter
{
public:
    SROpInterpreter();
    // Functions...
    double interpret(const QVector<ExpressionSymbol*>& symbols) const;

private:
    SROpInterpreter(const SROpInterpreter& obj);
    SROpInterpreter& operator=(const SROpInterpreter& obj);
};
#endif // SROPINTERPRETER_H
