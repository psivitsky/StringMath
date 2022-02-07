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
    SROpInterpreter();

    void    interpret(QString::const_iterator begin, QString::const_iterator end) const;
private:
    SROpInterpreter(const SROpInterpreter &obj);
    SROpInterpreter &operator=(const SROpInterpreter &obj);
};
#endif // SROPINTERPRETER_H
