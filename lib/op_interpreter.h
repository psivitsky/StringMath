//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * Algebraic operators interpreter
 * \details
 * Class description
 * -----
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef OPINTERPRETER_H
#define OPINTERPRETER_H

#include    <QVector>

#include    "string_math_base.h"
#include    "string_math_constant.h"

class OpInterpreter
{
public:
    virtual void    interpret(const QString &expressionStr, QString &interpretedExpStr) const = 0;
protected:
    OpInterpreter(const QVector<StringMathConstant> &constants);
    //Constants...
    const QString   opening_bracket = "(";
    const QString   closing_bracket = ")";

    static const int    precision = 16;
    //Functions...
    void    opening_bracket_skipping(QString::const_iterator &begin, QString::const_iterator end, QString &skippedStr) const;
    void    operand_processing(QString &operand) const;
    void    spaces_removing(QString &operand) const;
private:
    OpInterpreter(const OpInterpreter &obj);
    OpInterpreter &operator=(const OpInterpreter &obj);
    //Containers...
    QVector<StringMathConstant> constants_;
    //Functions...
    bool    operand_checking(const QString &operand) const;
    void    constant_replacing(QString &operand) const;
};
#endif // OPINTERPRETER_H
