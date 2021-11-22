//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * The "StringMath" test widget application
 * \details
 * The widget contains a line edit for entering an expression and spin box for displaying the calculation result.\n
 * If a calculation throws an exception, it will be printed in log text edit.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef INTERFACE_H
#define INTERFACE_H

#include    <QWidget>

#include    "string_math.h"

namespace Ui { class Interface; }

class Interface : public QWidget
{
    Q_OBJECT
public:
    explicit Interface(QWidget *parent = 0);
    ~Interface();
private slots:
    void    on_expression_LE_editingFinished();
private:
    Ui::Interface *ui;
    Interface(const Interface &obj);
    Interface &operator=(const Interface &obj);
};
#endif // INTERFACE_H
