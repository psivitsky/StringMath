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

#include    "string_math_base.h"
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

    void    analyze(QString::const_iterator begin, QString::const_iterator end, QString &calcResult) const;
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

    FuncInterpreter function;
    FROpInterpreter first_rang_operators;
    SROpInterpreter second_rang_operators;
    //Containers...
    QVector<StringMathConstant> constants_;
    QVector<StringMathFunction> functions_;
    //Functions...
    void    subexpression_finder() const;
    void    constants_replacer() const;
    void    rounder() const;
};
#endif // EXPRESSIONANALYZER_H
