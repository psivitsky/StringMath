//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Expression symbol
 * \details
 * Class description
 * -----
 * This is the base class of expression symbols. It provides the type of symbol.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef EXPRESSIONSYMBOL_H
#define EXPRESSIONSYMBOL_H

enum ExpressionSymbolType
{
    invalidType,
    expressionType,
    operatorType,
    operandType
};

class ExpressionSymbol
{
public:
    ExpressionSymbol();
    ExpressionSymbol(const ExpressionSymbol& obj) = default;
    ExpressionSymbol& operator=(const ExpressionSymbol& obj) = default;
    virtual ~ExpressionSymbol() = default;
    // Functions...
    ExpressionSymbolType symbol_type() const;

protected:
    // Variables...
    ExpressionSymbolType symbol_type_;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The constructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline ExpressionSymbol::ExpressionSymbol() : symbol_type_(invalidType)
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of getting the type of symbol.
 * \return Symbol type.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline ExpressionSymbolType ExpressionSymbol::symbol_type() const
{
    return symbol_type_;
}
#endif // EXPRESSIONSYMBOL_H
