#include "expression_symbol.h"
//----------------------------------------------------------------------------------
//! \details The constructor.
//----------------------------------------------------------------------------------
ExpressionSymbol::ExpressionSymbol() : symbol_type_(invalidType)
{
}
//----------------------------------------------------------------------------------
/*!
 * The function of getting the type of symbol.
 * \return Symbol type.
 */
//----------------------------------------------------------------------------------
ExpressionSymbolType ExpressionSymbol::symbol_type() const
{
    return symbol_type_;
}
