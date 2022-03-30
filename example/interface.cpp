#include "interface.h"
#include "ui_interface.h"

double sqr_example(double);

//----------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] parent Pointer to the parent widget.
 */
//----------------------------------------------------------------------------------
Interface::Interface(QWidget* parent) : QWidget(parent), ui(new Ui::Interface)
{
    ui->setupUi(this);
    ui->expression_result_SB->setRange(-__DBL_MAX__, __DBL_MAX__);

    calc.add_constant(StringMathConstant("2pi", 2 * M_PI));
    calc.add_function(StringMathFunction("sqr", sqr_example));
}
//----------------------------------------------------------------------------------
//! \details The destructor.
//----------------------------------------------------------------------------------
Interface::~Interface()
{
    delete ui;
}
//----------------------------------------------------------------------------------
//! \details The expression line edit slot.
//----------------------------------------------------------------------------------
void Interface::on_expression_LE_editingFinished()
{
    ui->log_LE->clear();

    try
    {
        ui->expression_result_SB->setValue(
            calc.calculate(ui->expression_LE->text()));
    }
    catch(StringMathError& err)
    {
        ui->log_LE->setText(err.what());
    }
}
//----------------------------------------------------------------------------------
/*!
 * Example of a square calculation function.
 * \param[in] val Function argument.
 */
//----------------------------------------------------------------------------------
double sqr_example(double val)
{
    return val * val;
}
