#include "expression.h"
//----------------------------------------------------------------------------------
//! \details The constructor.
//----------------------------------------------------------------------------------
Expression::Expression() : ExpressionOperand(), function_name_("")
{
    symbol_type_ = expressionType;
}
//----------------------------------------------------------------------------------
//! \details The destructor.
//----------------------------------------------------------------------------------
Expression::~Expression()
{
    foreach(ExpressionSymbol* symbol, symbols_)
        delete symbol;
}
//----------------------------------------------------------------------------------
/*!
 * The function of adding a new symbol.
 * \param[in] symbol Pointer to a new symbol.
 */
//----------------------------------------------------------------------------------
void Expression::add(ExpressionSymbol* symbol)
{
    symbols_.push_back(symbol);
}
//----------------------------------------------------------------------------------
/*!
 * The function of getting the expression symbols.
 * \return Container of expression symbols.
 */
//----------------------------------------------------------------------------------
const QVector<ExpressionSymbol*>& Expression::symbols() const
{
    return symbols_;
}
//----------------------------------------------------------------------------------
/*!
 * Method for setting the name of the expression function.
 * \param[in] functionName The name of the expression function.
 */
//----------------------------------------------------------------------------------
void Expression::set_function_name(const QString& functionName)
{
    function_name_ = functionName;
}
//----------------------------------------------------------------------------------
/*!
 * Method for getting the name of the expression function.
 * \return The name of the expression function.
 */
//----------------------------------------------------------------------------------
const QString& Expression::function_name() const
{
    return function_name_;
}
