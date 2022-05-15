#ifndef STRING_MATH_WIDGET_H
#define STRING_MATH_WIDGET_H

#include <QtCore/qglobal.h>

#if defined(STRINGMATHWIDGET_LIBRARY)
#define STRINGMATHWIDGET_EXPORT Q_DECL_EXPORT
#else
#define STRINGMATHWIDGET_EXPORT Q_DECL_IMPORT
#endif

namespace Ui
{
class StringMathWidget;
}

//----------------------------------------------------------------------------------
/*!
 * \brief
 * StringMath widget
 * \details
 * The class object provides a StringMath calculator widget.\n
 * It can have a minimized and expanded view.
 * When minimized, the widget contains a spin box for entering numbers.
 * When expanded, in addition to minimized view, the widget includes a line edit
 * for user expressions and a line edit for the output of the StringMath
 * calculator.\n
 * If the StringMath calculator throws an exception, it will be printed in the
 * output line edit.\n
 * The expanded view also contains a context menu (an object of the
 * StringMathMenu class) with available constants and functions.
 * \warning The widget is minimized by default.
 */
//----------------------------------------------------------------------------------

#include <QWidget>

class StringMath;
class StringMathMenu;

class STRINGMATHWIDGET_EXPORT StringMathWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StringMathWidget(QWidget* parent = nullptr);
    StringMathWidget(const StringMathWidget& obj) = delete;
    StringMathWidget& operator=(const StringMathWidget& obj) = delete;
    ~StringMathWidget();
    // Functions...
    void    set_expression(const QString& str);
    QString expression() const;
    double  value() const;

    void set_decimals(int val);
    int  decimals() const;

    void set_minimized(bool fMinimized);
    bool is_minimized();

    void set_spinbox_visible(bool fVisible);
    bool spinbox_visible();

    void set_enabled();
    void set_disabled();
private slots:
    void on_minimize_expand_PB_clicked();
    void on_result_SB_valueChanged(const QString& arg1);
    void on_expression_LE_editingFinished();
    void on_copy_PB_clicked();
    void on_cnst_and_func_PB_clicked();

    void append_string(const QString& str);

private:
    Ui::StringMathWidget* ui;
    // Constants...
    const QString minimized_symbol = "►";
    const QString expanded_symbol = "▼";

    const QString result_SB_ok_style = "color: rgb(0, 128, 0)";
    const QString result_SB_error_style = "color: rgb(128, 0, 0)";
    // Pointers...
    StringMath*     calc;
    StringMathMenu* menu;
};
#endif // STRING_MATH_WIDGET_H
