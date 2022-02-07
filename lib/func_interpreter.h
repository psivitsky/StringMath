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

class FuncInterpreter : public OpInterpreter
{
public:
    FuncInterpreter();

    void    interpret(QString::const_iterator begin, QString::const_iterator end) const;
private:
    FuncInterpreter(const FuncInterpreter &obj);
    FuncInterpreter &operator=(const FuncInterpreter &obj);
};
#endif // FUNCINTERPRETER_H
