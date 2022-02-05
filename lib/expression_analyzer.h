//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Analyzer of mathematical expression in QString format
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

class ExpressionAnalyzer
{
public:
    ExpressionAnalyzer(int precision,
                       const QVector<StringMathConstant> &constants,
                       const QVector<StringMathFunction> &functions);

    double  analyze(const QString &str);
private:
    ExpressionAnalyzer(const ExpressionAnalyzer &obj);
    ExpressionAnalyzer &operator=(const ExpressionAnalyzer &obj);
    //Constants...
    const QString   base_opening_bracket = "(";
    const QString   base_closing_bracket = ")";

    const QStringList   opening_brackets = {"(", "[", "{"};
    const QStringList   closing_brackets = {")", "]", "}"};

    const QStringList   operators = {"*", "/", "+", "-"};
};
#endif // EXPRESSIONANALYZER_H
