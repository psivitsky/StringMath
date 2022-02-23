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

#include    <QStringList>

#include    "string_math_constant.h"

#include    "func_interpreter.h"
#include    "fr_op_interpreter.h"
#include    "sr_op_interpreter.h"

class ExpressionAnalyzer
{
public:
    ExpressionAnalyzer(int precision,
                       const QVector<StringMathConstant> &constants,
                       const QVector<StringMathFunction> &functions);

    void    analyze(const QString &expressionStr, QString &calcResultStr) const;
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
    FROpInterpreter first_rank_operators_;
    SROpInterpreter second_rank_operators_;
    //Containers...
    QVector<StringMathConstant> constants_;
    QVector<StringMathFunction> functions_;
    //Functions...
    void    brackets_replacing(QString &expressionStr) const;

    void    parsing(const QString &expressionStr, QVector<StringMathSymbol> &symbols, QString &funcName) const;
    void    function_name_parsing(QString::const_iterator &begin, QString::const_iterator end, QString &funcName) const;
    void    opening_bracket_skipping(QString::const_iterator &begin, QString::const_iterator end) const;
    void    subexpression_parsing(QString::const_iterator &begin, QString::const_iterator end, QString &subExpressionStr) const;
    StringMathSymbol    &operand_parsing(QString &operandStr) const;
    StringMathSymbol    &last_operand_parsing(QString &operandStr) const;
    StringMathSymbol    &operator_parsing(const QChar &operatorChar) const;

    void    spaces_removing(QString &operand) const;
    bool    operand_checking(const QString &operand) const;
    void    constant_replacing(QString &operand) const;

    void    subexpression_processing(const QString &expressionStrBefore, QString &expressionStrAfter) const;
    int     subexpression_begin_searching(const QString &expressionStr, int findFrom) const;
    int     subexpression_end_searching(const QString &expressionStr, int findFrom) const;
};
#endif // EXPRESSIONANALYZER_H
