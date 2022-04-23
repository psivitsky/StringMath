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
 * \warning
 * The widget is minimized by default.
 */
//----------------------------------------------------------------------------------

#include <QWidget>

#include "string_math.h"

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
    void          set_expression(const QString& str);
    const QString expression() const;
    double        value() const;

    void set_decimals(int val);
    int  decimals() const;

    void set_minimized(bool fMinimized);
    bool is_minimized();

    void set_enabled();
    void set_disabled();
private slots:
    void on_minimize_expand_PB_clicked();
    void on_result_SB_valueChanged(const QString& arg1);
    void on_expression_LE_editingFinished();
    void on_cnst_and_func_PB_clicked();

    void append_string(const QString& str);

private:
    Ui::StringMathWidget* ui;
    // Constants...
    const QString minimized_symbol = "►";
    const QString expanded_symbol = "▼";

    const QString result_SB_ok_style = "color: rgb(0, 128, 0)";
    const QString result_SB_error_style = "color: rgb(128, 0, 0)";
    // Variables...
    StringMath calc;
    // Pointers...
    StringMathMenu* menu;
};
#endif // STRING_MATH_WIDGET_H
