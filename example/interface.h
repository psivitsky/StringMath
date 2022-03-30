#ifndef INTERFACE_H
#define INTERFACE_H

namespace Ui
{
class Interface;
}

//----------------------------------------------------------------------------------
/*!
 * \brief
 * Example application of using the "StringMath" library
 * \details
 * The widget contains a line edit for entering an expression and spin box for
 * displaying the calculation result.\n
 * If a calculation throws an exception, it will be printed in log line edit.
 */
//----------------------------------------------------------------------------------

#include <QWidget>

#include "string_math.h"

class Interface : public QWidget
{
    Q_OBJECT
public:
    explicit Interface(QWidget* parent = 0);
    Interface(const Interface& obj) = delete;
    Interface& operator=(const Interface& obj) = delete;
    ~Interface();
private slots:
    void on_expression_LE_editingFinished();

private:
    Ui::Interface* ui;
    // Variables...
    StringMath calc;
};
#endif // INTERFACE_H
