#include "string_math_widget.h"
#include "ui_string_math_widget.h"
//----------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] parent Pointer to the parent widget.
 */
//----------------------------------------------------------------------------------
StringMathWidget::StringMathWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::StringMathWidget)
{
    ui->setupUi(this);
}
//----------------------------------------------------------------------------------
//! \details The destructor.
//----------------------------------------------------------------------------------
StringMathWidget::~StringMathWidget()
{
    delete ui;
}
