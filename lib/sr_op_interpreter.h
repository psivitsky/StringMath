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

#include "string_math_base.h"

#include "expression.h"
#include "expression_operand.h"
#include "expression_operator.h"

#include <QVector>

class SROpInterpreter
{
public:
    SROpInterpreter();
    // Functions...
    double interpret(const QVector<ExpressionSymbol*>& symbols) const;

private:
    SROpInterpreter(const SROpInterpreter& obj);
    SROpInterpreter& operator=(const SROpInterpreter& obj);
    // Functions...
    ExpressionOperator*
    operator_checker(QVector<ExpressionSymbol*>::const_iterator begin,
                     QVector<ExpressionSymbol*>::const_iterator end) const;
    ExpressionOperand*
    operand_checker(QVector<ExpressionSymbol*>::const_iterator begin,
                    QVector<ExpressionSymbol*>::const_iterator end) const;
};
#endif // SROPINTERPRETER_H
