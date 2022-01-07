#include "interface.h"
#include "ui_interface.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] parent Pointer to the widget parent.
*/
//---------------------------------------------------------------------------------------------------------------------------------------------------
Interface::Interface(QWidget *parent) : QWidget(parent), ui(new Ui::Interface)
{
    ui->setupUi(this);

    ui->expression_result_SB->setRange( - __DBL_MAX__, __DBL_MAX__);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The destructor.
//---------------------------------------------------------------------------------------------------------------------------------------------------
Interface::~Interface()
{
    delete ui;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//! \details The expression line edit slot.
//---------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::on_expression_LE_editingFinished()
{
    try
    {
        StringMath calc(3);
        ui->expression_result_SB->setValue(calc.string_process(ui->expression_LE->text()));
    }
    catch(StringMathError &err)
    {
        ui->log_TE->append(err.msg);
    }
}
