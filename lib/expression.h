//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Expression operator
 * \details
 * Class description
 * -----
 * This class specifies an expression.
 * It is derived from the ExpressionSymbol class.
 * The class object contains symbols and subexpressions.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "expression_symbol.h"

#include <QVector>

class Expression : public ExpressionSymbol
{
public:
    Expression();
    Expression(const Expression& obj) = default;
    Expression& operator=(const Expression& obj) = default;
    ~Expression() = default;
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
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline Expression::Expression() : ExpressionSymbol()
{
    symbol_type_ = expressionType;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of adding a new symbol.
 * \param[in] symbol New symbol.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline void Expression::add(ExpressionSymbol* symbol)
{
    symbols_.push_back(symbol);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of getting the expression symbols.
 * \return Container of expression symbols.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline const QVector<ExpressionSymbol*>& Expression::symbols() const
{
    return symbols_;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Method for setting the name of the expression function.
 * \param[in] functionName The name of the expression function.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline void Expression::set_function_name(const QString& functionName)
{
    function_name_ = functionName;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * Method for getting the name of the expression function.
 * \return The name of the expression function.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline const QString& Expression::function_name() const
{
    return function_name_;
}
#endif // EXPRESSION_H
