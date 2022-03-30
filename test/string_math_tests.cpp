#include "string_math_tests.h"
#include "string_math.h"

#include <QFile>
#include <QTextStream>
#include <QTime>

struct TestInfo
{
    int     precision = 0;
    QString name = "";
    QString expression = "";
    QString result = "";
};

bool test_parser(const QString&, TestInfo&);

//----------------------------------------------------------------------------------
//! \details Summation random testing function.
//----------------------------------------------------------------------------------
void StringMathTests::sum_rand_tests()
{
    QTextStream out(stdout);
    out << "Summation check...\n";

    srand(QTime::currentTime().msec());

    StringMath calc;

    int failures_cnt = 0;
    int test_num = 0;
    while(test_num < rand_tests_num)
    {
        double op_1 = static_cast<double>(rand());
        double op_2 = static_cast<double>(rand());
        double result = op_1 + op_2;

        QString test_exp =
            QString::number(op_1, 'f', 0) + "+" + QString::number(op_2, 'f', 0);

        try
        {
            if(calc.calculate(test_exp) != result)
            {
                ++failures_cnt;
                out << "Failure!\t\t" << test_exp << "\n";
            }
        }
        catch(StringMathError& err)
        {
            out << "Exception!\t\t" << test_exp << "\t\t" << err.what() << "\n";
        }

        ++test_num;
    }

    if(failures_cnt == 0)
        out << "There were no failures!\n\n";
    else
        out << "\nNumber of failures: " << failures_cnt << "!\n\n";
}
//----------------------------------------------------------------------------------
//! \details Difference random testing function.
//----------------------------------------------------------------------------------
void StringMathTests::diff_rand_tests()
{
    QTextStream out(stdout);
    out << "Difference check...\n";

    srand(QTime::currentTime().msec());

    StringMath calc;

    int failures_cnt = 0;
    int test_num = 0;
    while(test_num < rand_tests_num)
    {
        double op_1 = static_cast<double>(rand());
        double op_2 = static_cast<double>(rand());
        double result = op_1 - op_2;

        QString test_exp =
            QString::number(op_1, 'f', 0) + "-" + QString::number(op_2, 'f', 0);

        try
        {
            if(calc.calculate(test_exp) != result)
            {
                ++failures_cnt;
                out << "Failure!\t\t" << test_exp << "\n";
            }
        }
        catch(StringMathError& err)
        {
            out << "Exception!\t\t" << test_exp << "\t\t" << err.what() << "\n";
        }

        ++test_num;
    }

    if(failures_cnt == 0)
        out << "There were no failures!\n\n";
    else
        out << "\nNumber of failures: " << failures_cnt << "!\n\n";
}
//----------------------------------------------------------------------------------
//! \details Product random testing function.
//----------------------------------------------------------------------------------
void StringMathTests::prod_rand_tests()
{
    QTextStream out(stdout);
    out << "Product check...\n";

    srand(QTime::currentTime().msec());

    StringMath calc;

    int failures_cnt = 0;
    int test_num = 0;
    while(test_num < rand_tests_num)
    {
        double op_1 = static_cast<double>(rand());
        double op_2 = static_cast<double>(rand());
        double result = op_1 * op_2;

        QString test_exp =
            QString::number(op_1, 'f', 0) + "*" + QString::number(op_2, 'f', 0);

        try
        {
            if(calc.calculate(test_exp) != result)
            {
                ++failures_cnt;
                out << "Failure!\t\t" << test_exp << "\n";
            }
        }
        catch(StringMathError& err)
        {
            out << "Exception!\t\t" << test_exp << "\t\t" << err.what() << "\n";
        }

        ++test_num;
    }

    if(failures_cnt == 0)
        out << "There were no failures!\n\n";
    else
        out << "\nNumber of failures: " << failures_cnt << "!\n\n";
}
//----------------------------------------------------------------------------------
//! \details Division random testing function.
//----------------------------------------------------------------------------------
void StringMathTests::div_rand_tests()
{
    QTextStream out(stdout);
    out << "Division check...\n";

    srand(QTime::currentTime().msec());

    StringMath calc;

    int failures_cnt = 0;
    int test_num = 0;
    while(test_num < rand_tests_num)
    {
        double op_1 = static_cast<double>(rand());
        double op_2 = static_cast<double>(rand());
        double result = op_1 / op_2;

        QString test_exp =
            QString::number(op_1, 'f', 0) + "/" + QString::number(op_2, 'f', 0);

        try
        {
            if(calc.calculate(test_exp) != result)
            {
                ++failures_cnt;
                out << "Failure!\t\t" << test_exp << "\n";
            }
        }
        catch(StringMathError& err)
        {
            out << "Exception!\t\t" << test_exp << "\t\t" << err.what() << "\n";
        }

        ++test_num;
    }

    if(failures_cnt == 0)
        out << "There were no failures!\n\n";
    else
        out << "\nNumber of failures: " << failures_cnt << "!\n\n";
}
//----------------------------------------------------------------------------------
//! \details The function of specific tests.
//----------------------------------------------------------------------------------
void StringMathTests::file_tests()
{
    QTextStream out(stdout);
    out << "Specific tests from the file...\n";

    QFile f(":/txt/test.txt");
    if(!f.open(QFile::ReadOnly))
        out << "Cannot open the file with the tests!\n";

    StringMath calc;

    int failures_cnt = 0;

    QString     line = "";
    QTextStream in(&f);
    while(in.readLineInto(&line))
    {
        if(line.isEmpty())
            continue;

        TestInfo test;
        if(!test_parser(line, test))
        {
            out << "Test parsing failure! \"" << line << "\"\n";
            continue;
        }

        try
        {
            if(calc.calculate(test.expression, test.precision) != test.result)
            {
                ++failures_cnt;
                out << "Failure!\t\t" << test.name << "\n";
            }
        }
        catch(StringMathError& err)
        {
            out << "Exception!\t\t" << test.name << "\t\t" << err.what()
                << "\n";
        }
    }

    f.close();

    if(failures_cnt == 0)
        out << "There were no failures!\n\n";
    else
        out << "\nNumber of failures: " << failures_cnt << "!\n\n";
}
//----------------------------------------------------------------------------------
/*!
 * The function of parsing the test string.\n
 * The test syntax is as follows:
 * |test_name,calculation_precision,expression_string=calculation_result|
 * \param[in] str The test string.
 * \param[out] test Parsed test information.
 */
//----------------------------------------------------------------------------------
bool test_parser(const QString& testStr, TestInfo& test)
{
    QRegExp test_str_checker("^\\|\\w+\\,\\d+\\,[^=]+\\=[^|]+\\|$");
    if(!test_str_checker.exactMatch(testStr))
        return false;

    int begin_pos = testStr.indexOf("|");
    int prec_pos = testStr.indexOf(",");
    int exp_pos = testStr.lastIndexOf(",");
    int res_pos = testStr.lastIndexOf("=");
    int end_pos = testStr.lastIndexOf("|");

    test.name = testStr.mid(begin_pos + 1, prec_pos - begin_pos - 1);
    test.precision = testStr.mid(prec_pos + 1, exp_pos - prec_pos - 1).toInt();

    test.expression = testStr.mid(exp_pos + 1, res_pos - exp_pos - 1);

    double res_val = testStr.mid(res_pos + 1, end_pos - res_pos - 1).toDouble();
    test.result = QString::number(res_val, 'f', test.precision);

    return true;
}
