#ifndef STRINGMATHMENU_H
#define STRINGMATHMENU_H

#include <QMenu>

//----------------------------------------------------------------------------------
//! \details The structure with some menu data.
//----------------------------------------------------------------------------------
struct StringMathMenuData
{
    QString actionName;
    QString str;
};

//----------------------------------------------------------------------------------
/*!
 * \brief
 * The context menu of StringMath constants and functions
 * \details
 */
//----------------------------------------------------------------------------------
class StringMathMenu : public QMenu
{
    Q_OBJECT
public:
    explicit StringMathMenu(QWidget* parent = nullptr);
    StringMathMenu(const StringMathMenu& obj) = delete;
    StringMathMenu& operator=(const StringMathMenu& obj) = delete;
    ~StringMathMenu() = default;

private:
    // Constants...
    const QString constants_submenu_name_ = "Constants";
    const QString functions_submenu_name_ = "Functions";
    const QString basic_functions_submenu_name_ = "Basic";
    const QString trigonometric_functions_submenu_name_ = "Trigonometric";
    const QString logarithmic_functions_submenu_name_ = "Logarithmic";

    const QVector<StringMathMenuData> constants_ = {{"π", "pi"},
                                                    {"Exponent", "e"}};

    const QVector<StringMathMenuData> basic_functions_ = {
        {"Square root", "sqrt()"}};

    const QVector<StringMathMenuData> trigonometric_functions_ = {
        {"Cosine", "cos()"},
        {"Sine", "sin()"},
        {"Tangent", "tan()"},
        {"Cotangent", "cot()"},
        {"Arccosine", "acos()"},
        {"Arcsine", "asin()"},
        {"Arctangent", "atan()"},
        {"Arccotangent", "acot()"}};

    const QVector<StringMathMenuData> logarithmic_functions_ = {
        {"Natural logarithm", "log()"},
        {"Base 10 logarithm", "log10()"},
        {"Base 2 logarithm", "log2()"},
        {"Exponent", "exp()"}};

    // Functions...
    void add_action(const QString& actionName, QMenu* targetSubmenu);
};
#endif // STRINGMATHMENU_H
