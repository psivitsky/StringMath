#include "interface.h"
#include "ui_interface.h"
//----------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] parent Pointer to the parent widget.
 */
//----------------------------------------------------------------------------------
Interface::Interface(QWidget* parent) : QWidget(parent), ui(new Ui::Interface)
{
    ui->setupUi(this);

    ui->calc_W->set_decimals(decimals_number);
    ui->calc_W->set_expression(default_expression);
}
//----------------------------------------------------------------------------------
//! \details The destructor.
//----------------------------------------------------------------------------------
Interface::~Interface()
{
    delete ui;
}
