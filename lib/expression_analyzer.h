//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Analyzer of mathematical expression
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef EXPRESSIONANALYZER_H
#define EXPRESSIONANALYZER_H

#include "math_parser.h"

#include "fr_op_interpreter.h"
#include "func_interpreter.h"
#include "sr_op_interpreter.h"

class ExpressionAnalyzer
{
public:
    ExpressionAnalyzer(int                                precision,
                       const QVector<StringMathConstant>& constants,
                       const QVector<StringMathFunction>& functions);

    void analyze(const QString& expressionStr, QString& calcResultStr) const;

private:
    ExpressionAnalyzer(const ExpressionAnalyzer& obj);
    ExpressionAnalyzer& operator=(const ExpressionAnalyzer& obj);
    // Variables...
    int precision_;

    FuncInterpreter function_;
    FROpInterpreter first_rank_operators_;
    SROpInterpreter second_rank_operators_;
    // Containers...
    QVector<StringMathConstant> constants_;
    QVector<StringMathFunction> functions_;
    // Functions...
    double calculate(const Expression* expression,
                     const QString&    funcName) const;
};
#endif // EXPRESSIONANALYZER_H
