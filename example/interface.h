#ifndef INTERFACE_H
#define INTERFACE_H

namespace Ui
{
class Interface;
}

//----------------------------------------------------------------------------------
/*!
 * \brief
 * Example application of using the StringMath library
 * \details
 * The application contains a StringMathWidget object - an interface to the
 * StringMath calculator.
 */
//----------------------------------------------------------------------------------

#include <QWidget>

class Interface : public QWidget
{
    Q_OBJECT
public:
    explicit Interface(QWidget* parent = 0);
    Interface(const Interface& obj) = delete;
    Interface& operator=(const Interface& obj) = delete;
    ~Interface();

private:
    Ui::Interface* ui;
    // Constants...
    static const int decimals_number = 5;

    const QString default_expression = "1.";
};
#endif // INTERFACE_H
