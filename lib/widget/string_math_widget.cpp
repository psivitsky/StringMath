#include "string_math_widget.h"
#include "ui_string_math_widget.h"

#include "string_math_menu.h"

//----------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] parent Pointer to the parent widget.
 */
//----------------------------------------------------------------------------------
StringMathWidget::StringMathWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::StringMathWidget),
      menu(new StringMathMenu(this))
{
    ui->setupUi(this);

    set_minimized(true);

    connect(menu,
            SIGNAL(data_selected(const QString&)),
            SLOT(append_string(const QString&)));
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
 * Expression string setter.
 * \param[in] str The expression string.
 */
//----------------------------------------------------------------------------------
void StringMathWidget::set_expression(const QString& str)
{
    ui->expression_LE->setText(str);
    on_expression_LE_editingFinished();
}
//----------------------------------------------------------------------------------
/*!
 * Expression string getter.
 * \return The expression string.
 */
//----------------------------------------------------------------------------------
const QString StringMathWidget::expression() const
{
    return ui->expression_LE->text();
}
//----------------------------------------------------------------------------------
/*!
 * Calculation result getter.
 * \return The calculation result.
 */
//----------------------------------------------------------------------------------
double StringMathWidget::value() const
{
    return ui->result_SB->value();
}
//----------------------------------------------------------------------------------
/*!
 * Calculation precision setter.
 * \param[in] val The calculation precision.
 */
//----------------------------------------------------------------------------------
void StringMathWidget::set_decimals(int val)
{
    ui->result_SB->setDecimals(val);
}
//----------------------------------------------------------------------------------
/*!
 * Calculation precision getter.
 * \return The calculation precision.
 */
//----------------------------------------------------------------------------------
int StringMathWidget::decimals() const
{
    return ui->result_SB->decimals();
}
//----------------------------------------------------------------------------------
/*!
 * Minimized view setter.
 * \param[in] fMinimized The flag of the minimized view:
 * true - the widget view is minimized,
 * false - the widget is expanded.
 */
//----------------------------------------------------------------------------------
void StringMathWidget::set_minimized(bool fMinimized)
{
    if(fMinimized)
    {
        ui->minimize_expand_PB->setText(minimized_symbol);
        ui->calculator_frame->hide();
    }
    else
    {
        ui->minimize_expand_PB->setText(expanded_symbol);
        ui->calculator_frame->show();
    }
}
//----------------------------------------------------------------------------------
/*!
 * Minimized view checker.
 * \return The check result: true - the widget view is minimized,
 * false - the widget is expanded.
 */
//----------------------------------------------------------------------------------
bool StringMathWidget::is_minimized()
{
    return ui->calculator_frame->isHidden();
}
//----------------------------------------------------------------------------------
//! \details The widget enabling function.
//----------------------------------------------------------------------------------
void StringMathWidget::set_enabled()
{
    ui->result_SB->setEnabled(true);
    ui->expression_LE->setEnabled(true);
    ui->result_LE->setEnabled(true);
    ui->cnst_and_func_PB->setEnabled(true);
}
//----------------------------------------------------------------------------------
//! \details The widget disabling function.
//----------------------------------------------------------------------------------
void StringMathWidget::set_disabled()
{
    ui->result_SB->setDisabled(true);
    ui->expression_LE->setDisabled(true);
    ui->result_LE->setDisabled(true);
    ui->cnst_and_func_PB->setDisabled(true);
}
//----------------------------------------------------------------------------------
//! \details The widget minimizing/expanding slot.
//----------------------------------------------------------------------------------
void StringMathWidget::on_minimize_expand_PB_clicked()
{
    if(is_minimized())
        set_minimized(false);
    else
        set_minimized(true);
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
    QString expression_str = arg1;
    ui->expression_LE->setText(expression_str.replace(',', '.'));

    try
    {
        QString result_str = calc.calculate(ui->expression_LE->text(),
                                            ui->result_SB->decimals());

        ui->result_LE->setStyleSheet(result_SB_ok_style);
        ui->result_LE->setText(result_str);
    }
    catch(StringMathError& err)
    {
        ui->result_LE->setStyleSheet(result_SB_error_style);
        ui->result_LE->setText(err.what());
    }
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
        QString result_str = calc.calculate(ui->expression_LE->text(),
                                            ui->result_SB->decimals());

        ui->result_LE->setStyleSheet(result_SB_ok_style);
        ui->result_LE->setText(result_str);

        ui->result_SB->blockSignals(true);
        ui->result_SB->setValue(ui->result_LE->text().toDouble());
        ui->result_SB->blockSignals(false);
    }
    catch(StringMathError& err)
    {
        ui->result_LE->setStyleSheet(result_SB_error_style);
        ui->result_LE->setText(err.what());
    }
}
//----------------------------------------------------------------------------------
//! \details Slot for displaying the context menu of constants and functions.
//----------------------------------------------------------------------------------
void StringMathWidget::on_cnst_and_func_PB_clicked()
{
    menu->popup(ui->cnst_and_func_PB->mapToGlobal(QPoint(0, 0)));
}
//----------------------------------------------------------------------------------
/*!
 * Slot for appending a string to the expression text.
 * \param[in] str The appending string.
 */
//----------------------------------------------------------------------------------
void StringMathWidget::append_string(const QString& str)
{
    ui->expression_LE->setText(ui->expression_LE->text() + str);
}
