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
    subExpressionType,
    operatorType,
    operandType,
    emptyOperandType
};

class ExpressionSymbol
{
public:
    // Functions...
    ExpressionSymbolType type();

protected:
    ExpressionSymbol();
    ExpressionSymbol(const ExpressionSymbol& obj) = default;
    ExpressionSymbol& operator=(const ExpressionSymbol& obj) = default;
    virtual ~ExpressionSymbol() = default;
    // Variables...
    ExpressionSymbolType type_;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The function of getting the type of symbol.
 * \return Symbol type.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
inline ExpressionSymbolType ExpressionSymbol::type()
{
    return type_;
}
#endif // EXPRESSIONSYMBOL_H
