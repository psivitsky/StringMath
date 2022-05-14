#ifndef STRINGMATHTESTS_H
#define STRINGMATHTESTS_H

//----------------------------------------------------------------------------------
//! \details Namespace with tests of the "StringMath" library.
//----------------------------------------------------------------------------------
namespace StringMathTests
{
static const int rand_tests_num = 1000;

void sum_rand_tests();
void diff_rand_tests();
void prod_rand_tests();
void div_rand_tests();
void pow_rand_tests();

void file_tests();
}; // namespace StringMathTests

#endif // STRINGMATHTESTS_H
