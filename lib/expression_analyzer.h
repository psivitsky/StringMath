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

#include    <QVector>
#include    <QStringList>

#include    "string_math_constant.h"
#include    "string_math_function.h"

#include    "func_interpreter.h"
#include    "fr_op_interpreter.h"
#include    "sr_op_interpreter.h"

class ExpressionAnalyzer
{
public:
    ExpressionAnalyzer(int precision,
                       const QVector<StringMathConstant> &constants,
                       const QVector<StringMathFunction> &functions);

    void    analyze(const QString &strExpression, QString &calcResult) const;
private:
    ExpressionAnalyzer(const ExpressionAnalyzer &obj);
    ExpressionAnalyzer &operator=(const ExpressionAnalyzer &obj);
    //Constants...
    const QString   base_opening_bracket = "(";
    const QString   base_closing_bracket = ")";

    const QStringList   opening_brackets = {"(", "[", "{"};
    const QStringList   closing_brackets = {")", "]", "}"};

    const QStringList   operators = {"*", "/", "+", "-"};
    //Variables...
    int precision_;

    FuncInterpreter function_;
    FROpInterpreter first_rang_operators_;
    SROpInterpreter second_rang_operators_;
    //Containers...
    QVector<StringMathConstant> constants_;
    QVector<StringMathFunction> functions_;
    //Functions...
    void    subexpression_finder() const;
    void    constants_replacer() const;
    void    rounder() const;
};
#endif // EXPRESSIONANALYZER_H
