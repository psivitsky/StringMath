#include "string_math_menu.h"
//----------------------------------------------------------------------------------
/*!
 * The constructor.
 * \param[in] parent Pointer to the parent widget.
 */
//----------------------------------------------------------------------------------
StringMathMenu::StringMathMenu(QWidget* parent) : QMenu(parent)
{
    QMenu* constants_submenu = new QMenu("Constants", this);
    addMenu(constants_submenu);

    QAction* constant_pi = new QAction("π", this);
    constants_submenu->addAction(constant_pi);
    QAction* constant_e = new QAction("e", this);
    constants_submenu->addAction(constant_e);

    QMenu* functions_submenu = new QMenu("Functions", this);
    addMenu(functions_submenu);

    QMenu* functions_basic_submenu = new QMenu("Basic", this);
    functions_submenu->addMenu(functions_basic_submenu);
    QAction* function_sqrt = new QAction("Square root", this);
    functions_basic_submenu->addAction(function_sqrt);

    QMenu* functions_trigonometric_submenu = new QMenu("Trigonometric", this);
    functions_submenu->addMenu(functions_trigonometric_submenu);
    QAction* function_cos = new QAction("Cosine", this);
    functions_trigonometric_submenu->addAction(function_cos);
    QAction* function_sin = new QAction("Sine", this);
    functions_trigonometric_submenu->addAction(function_sin);
    QAction* function_tan = new QAction("Tangent", this);
    functions_trigonometric_submenu->addAction(function_tan);
    QAction* function_cot = new QAction("Cotangent", this);
    functions_trigonometric_submenu->addAction(function_cot);
    functions_trigonometric_submenu->addSeparator();
    QAction* function_acos = new QAction("Arccosine", this);
    functions_trigonometric_submenu->addAction(function_acos);
    QAction* function_asin = new QAction("Arcsine", this);
    functions_trigonometric_submenu->addAction(function_asin);
    QAction* function_atan = new QAction("Arctangent", this);
    functions_trigonometric_submenu->addAction(function_atan);
    QAction* function_acot = new QAction("Arccotangent", this);
    functions_trigonometric_submenu->addAction(function_acot);

    QMenu* functions_logarithmic_submenu = new QMenu("Logarithmic", this);
    functions_submenu->addMenu(functions_logarithmic_submenu);
    QAction* function_log = new QAction("Natural logarithm", this);
    functions_logarithmic_submenu->addAction(function_log);
    QAction* function_log10 = new QAction("Base 10 logarithm", this);
    functions_logarithmic_submenu->addAction(function_log10);
    QAction* function_log2 = new QAction("Base 2 logarithm", this);
    functions_logarithmic_submenu->addAction(function_log2);
    QAction* function_exp = new QAction("Exponent", this);
    functions_logarithmic_submenu->addAction(function_exp);
}
