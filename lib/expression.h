//----------------------------------------------------------------------------------
/*!
 * \brief
 * Expression operator
 * \details
 * Class description
 * -----
 * This class specifies an expression.
 * It is derived from the ExpressionOperand class.
 * The class object contains symbols and subexpressions.
 * The Expression object can be an argument to a function with the specified
 * name.
 * As an ExpressionOperand object, the Expression object after calculations can
 * have some value.
 */
//----------------------------------------------------------------------------------
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "expression_operand.h"

#include <QVector>

class Expression : public ExpressionOperand
{
public:
    Expression();
    Expression(const Expression& obj) = default;
    Expression& operator=(const Expression& obj) = default;
    ~Expression();
    // Functions...
    void                              add(ExpressionSymbol* symbol);
    const QVector<ExpressionSymbol*>& symbols() const;

    void           set_function_name(const QString& functionName);
    const QString& function_name() const;

private:
    // Variables...
    QString function_name_;
    // Containers...
    QVector<ExpressionSymbol*> symbols_;
};
#endif // EXPRESSION_H
