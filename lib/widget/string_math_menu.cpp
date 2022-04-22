#include "string_math_menu.h"
//----------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] parent Pointer to the parent widget.
 */
//----------------------------------------------------------------------------------
StringMathMenu::StringMathMenu(QWidget* parent) : QMenu(parent)
{
    QMenu* constants_submenu = new QMenu(constants_submenu_name_, this);
    addMenu(constants_submenu);
    for(int i = 0; i < constants_.size(); ++i)
        add_action(constants_.at(i).actionName, constants_submenu);

    QMenu* functions_submenu = new QMenu(functions_submenu_name_, this);
    addMenu(functions_submenu);

    QMenu* functions_basic_submenu =
        new QMenu(basic_functions_submenu_name_, this);
    functions_submenu->addMenu(functions_basic_submenu);
    for(int i = 0; i < basic_functions_.size(); ++i)
        add_action(basic_functions_.at(i).actionName, functions_basic_submenu);

    QMenu* functions_trigonometric_submenu =
        new QMenu(trigonometric_functions_submenu_name_, this);
    functions_submenu->addMenu(functions_trigonometric_submenu);
    for(int i = 0; i < trigonometric_functions_.size(); ++i)
        add_action(trigonometric_functions_.at(i).actionName,
                   functions_trigonometric_submenu);

    QMenu* functions_logarithmic_submenu =
        new QMenu(logarithmic_functions_submenu_name_, this);
    functions_submenu->addMenu(functions_logarithmic_submenu);
    for(int i = 0; i < logarithmic_functions_.size(); ++i)
        add_action(logarithmic_functions_.at(i).actionName,
                   functions_logarithmic_submenu);
}
//----------------------------------------------------------------------------------
/*!
 * The function of adding an action to the submenu.
 * \param[in] actionName The name of the action.
 * \param[in] targetSubmenu Pointer to the target submenu.
 */
//----------------------------------------------------------------------------------
void StringMathMenu::add_action(const QString& actionName, QMenu* targetSubmenu)
{
    QAction* new_action = new QAction(actionName, this);
    targetSubmenu->addAction(new_action);
}
