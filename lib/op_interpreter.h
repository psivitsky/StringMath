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

#include    "string_math_base.h"

class OpInterpreter
{
public:
    virtual void    interpret(QString &strExpression) const = 0;
protected:
    OpInterpreter();
private:
    OpInterpreter(const OpInterpreter &obj);
    OpInterpreter &operator=(const OpInterpreter &obj);
};
#endif // OPINTERPRETER_H