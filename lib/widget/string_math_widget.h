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

class StringMathWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StringMathWidget(QWidget* parent = nullptr);
    ~StringMathWidget();

private:
    Ui::StringMathWidget* ui;
};
#endif // STRING_MATH_WIDGET_H
