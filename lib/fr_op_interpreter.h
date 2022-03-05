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

#include "string_math_base.h"

#include "expression.h"
#include "expression_operand.h"
#include "expression_operator.h"

#include <QVector>

class FROpInterpreter
{
public:
    FROpInterpreter();
    // Functions...
    void interpret(const QVector<ExpressionSymbol*>& symbolsBefore,
                   QVector<ExpressionSymbol*>&       symbolsAfter) const;

private:
    FROpInterpreter(const FROpInterpreter& obj);
    FROpInterpreter& operator=(const FROpInterpreter& obj);
    // Constants...
    const QVector<ExpressionOperatorType> first_rank_operators = {multType,
                                                                  divType};
    const QVector<ExpressionOperatorType> second_rank_operators = {sumType,
                                                                   diffType};
    // Functions...
    ExpressionOperator*
    operator_checker(QVector<ExpressionSymbol*>::const_iterator begin,
                     QVector<ExpressionSymbol*>::const_iterator end) const;
    ExpressionOperand*
    operand_checker(QVector<ExpressionSymbol*>::const_iterator begin,
                    QVector<ExpressionSymbol*>::const_iterator end) const;

    ExpressionOperand* first_rank_operation_processing(
        const ExpressionOperand*  leftOperand,
        const ExpressionOperator* centerOperator,
        const ExpressionOperand*  rightOperand) const;
};
#endif // FROPINTERPRETER_H
