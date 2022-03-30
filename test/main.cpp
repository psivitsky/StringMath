//----------------------------------------------------------------------------------
/*!
 * \brief
 * Console application for testing the "StringMath" library
 * \details
 * The application runs several simple random tests of basic mathematical
 * operations. Specific tests are taken from the text file "rest.txt" in
 * resources.qrc. The test syntax in the text file is as follows:
 * |test_name,calculation_precision,expression_string=calculation_result|
 */
//----------------------------------------------------------------------------------

#include <QCoreApplication>

#include "string_math_tests.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    StringMathTests::sum_rand_tests();
    StringMathTests::diff_rand_tests();
    StringMathTests::prod_rand_tests();
    StringMathTests::div_rand_tests();
    StringMathTests::file_tests();

    return 0;
}
