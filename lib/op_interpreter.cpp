#include "op_interpreter.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] constants The container with constants (StringMathConstant objects).
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
OpInterpreter::OpInterpreter(const QVector<StringMathConstant> &constants) : constants_(constants)
{

}
