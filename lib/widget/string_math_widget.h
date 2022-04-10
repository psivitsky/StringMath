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
 */
//----------------------------------------------------------------------------------

#include <QWidget>

#include "string_math.h"

class StringMathWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StringMathWidget(QWidget* parent = nullptr);
    ~StringMathWidget();

private slots:
    void on_result_SB_valueChanged(const QString& arg1);
    void on_expression_LE_editingFinished();

private:
    Ui::StringMathWidget* ui;
    // Variables...
    StringMath calc;
};
#endif // STRING_MATH_WIDGET_H
