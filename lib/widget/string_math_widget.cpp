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
//----------------------------------------------------------------------------------
/*!
 * Slot for processing the entered value.\n
 * Processing is performed every time the value changes.
 * \param[in] arg1 The entered value string.
 */
//----------------------------------------------------------------------------------
void StringMathWidget::on_result_SB_valueChanged(const QString& arg1)
{
    ui->expression_LE->setText(arg1);
}
//----------------------------------------------------------------------------------
/*!
 * Slot for calculating the entered expression.\n
 * The calculation is performed only after the expression editing is completed.
 * \param[in] arg1 The entered value string.
 */
//----------------------------------------------------------------------------------
void StringMathWidget::on_expression_LE_editingFinished()
{
    try
    {
        ui->result_LE->setText(calc.calculate(ui->expression_LE->text(),
                                              ui->result_SB->decimals()));

        ui->result_SB->blockSignals(true);
        ui->result_SB->setValue(ui->result_LE->text().toDouble());
        ui->result_SB->blockSignals(false);
    }
    catch(StringMathError& err)
    {
        ui->result_LE->setText(err.what());
    }
}
