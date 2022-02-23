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

#include    "string_math_base.h"

#include    <QVector>

class FROpInterpreter
{
public:
    FROpInterpreter();
    //Functions...
    void    interpret(const QVector<StringMathSymbol> &symbolsBefore,
                      QVector<StringMathSymbol> &symbolsAfter) const;
private:
    FROpInterpreter(const FROpInterpreter &obj);
    FROpInterpreter &operator=(const FROpInterpreter &obj);
    //Constants...
    const QVector<StringMathSymbolType> first_rank_operators = {multOperatorType, divOperatorType};
    const QVector<StringMathSymbolType> second_rank_operators = {sumOperatorType, diffOperatorType};
    //Functions...
    void    operation_parser(QVector<StringMathSymbol>::const_iterator &begin,
                             QVector<StringMathSymbol>::const_iterator end,
                             StringMathSymbol &centerOperator,
                             StringMathSymbol &rightOperand) const;

    void    first_rank_operation_processing(StringMathSymbol &leftOperand,
                                            const StringMathSymbol &centerOperator,
                                            const StringMathSymbol &rightOperand) const;
    void    second_rank_operation_processing(StringMathSymbol &leftOperand,
                                             const StringMathSymbol &centerOperator,
                                             const StringMathSymbol &rightOperand,
                                             QVector<StringMathSymbol> &symbolsAfter) const;
};
#endif // FROPINTERPRETER_H
