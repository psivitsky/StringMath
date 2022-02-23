//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * The "StringMath" test console application
 * \details
 * Create a text file in the application folder with test expressions.
 * The test syntax is as follows: |test_name,calc_precision,expression_str=calc_result|
 * After that run the application and see the test results in the terminal.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------

#include    <QCoreApplication>

#include    <QFile>
#include    <QTime>
#include    <QTextStream>

#include    "string_math.h"

static const int    rand_checks_num = 1000;

bool    test_str_parser(const QString &testStr,
                        QString &testName,
                        int &testPrec,
                        QString &testExp,
                        double &testRes);

void    sum_rand_tests();
void    diff_rand_tests();
void    prod_rand_tests();
void    div_rand_tests();

void    file_tests();

const QString file_name = "test.txt";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    sum_rand_tests();
    diff_rand_tests();
    prod_rand_tests();
    div_rand_tests();

    file_tests();

    return 0;
}

bool test_str_parser(const QString &testStr, QString &testName, int &testPrec, QString &testExp, QString &testRes)
{
    testName = "";
    testExp = "";
    testRes = "";

    QRegExp test_str_checker("^\\|\\w+\\,\\d+\\,[^=]+\\=[^|]+\\|$");

    if(!test_str_checker.exactMatch(testStr))
        return false;

    testName = testStr.mid(testStr.indexOf("|") + 1, testStr.indexOf(",") - testStr.indexOf("|") - 1);
    testPrec = testStr.mid(testStr.indexOf(",") + 1, testStr.lastIndexOf(",") - testStr.indexOf(",") - 1).toInt();
    testExp = testStr.mid(testStr.lastIndexOf(",") + 1, testStr.indexOf("=") - testStr.lastIndexOf(",") - 1);

    double test_res_val = testStr.mid(testStr.indexOf("=") + 1, testStr.lastIndexOf("|") - testStr.indexOf("=") - 1).toDouble();
    testRes = QString::number(test_res_val, 'f', testPrec);

    return true;
}

void sum_rand_tests()
{
    int failure_cnt = 0;
    double op_1 = 0.;
    double op_2 = 0.;

    QString result = "";
    QString test_exp = "";
    QString test_result = "";

    StringMath calc;

    QTextStream out(stdout);
    out << "Sum check...\n";

    srand(QTime::currentTime().msec());

    int check_num = 0;
    while(check_num < rand_checks_num)
    {
        op_1 = static_cast<double>(rand());
        op_2 = static_cast<double>(rand());
        result = QString::number(op_1 + op_2, 'f', calc.precision());

        test_exp = QString::number(op_1, 'f', calc.precision()) + "+" + QString::number(op_2, 'f', calc.precision());
        calc.calculate(test_exp, test_result);

        try
        {
            if(result != test_result)
            {
                ++failure_cnt;
                out << "Failure!\t\t" << test_exp << "\n";
            }
        }
        catch(StringMathError &err)
        {
            out << "Exception!\t\t" << test_exp << "\t\t" << err.what() << "\n";
        }

        ++check_num;
    }

    if(failure_cnt == 0)
        out << "There are no failures!\n\n";
    else
        out << "\nThere are " << failure_cnt << " failures!\n\n";
}

void diff_rand_tests()
{
    int failure_cnt = 0;
    double op_1 = 0.;
    double op_2 = 0.;

    QString result = "";
    QString test_exp = "";
    QString test_result = "";

    StringMath calc;

    QTextStream out(stdout);
    out << "Difference check...\n";

    srand(QTime::currentTime().msec());

    int check_num = 0;
    while(check_num < rand_checks_num)
    {
        op_1 = static_cast<double>(rand());
        op_2 = static_cast<double>(rand());
        result = QString::number(op_1 - op_2, 'f', calc.precision());

        test_exp = QString::number(op_1, 'f', calc.precision()) + "-" + QString::number(op_2, 'f', calc.precision());
        calc.calculate(test_exp, test_result);

        try
        {
            if(result != test_result)
            {
                ++failure_cnt;
                out << "Failure!\t\t" << test_exp << "\n";
            }
        }
        catch(StringMathError &err)
        {
            out << "Exception!\t\t" << test_exp << "\t\t" << err.what() << "\n";
        }

        ++check_num;
    }

    if(failure_cnt == 0)
        out << "There are no failures!\n\n";
    else
        out << "\nThere are " << failure_cnt << " failures!\n\n";
}

void prod_rand_tests()
{
    int failure_cnt = 0;
    double op_1 = 0.;
    double op_2 = 0.;

    QString result = "";
    QString test_exp = "";
    QString test_result = "";

    StringMath calc;

    QTextStream out(stdout);
    out << "Product check...\n";

    srand(QTime::currentTime().msec());

    int check_num = 0;
    while(check_num < rand_checks_num)
    {
        op_1 = static_cast<double>(rand());
        op_2 = static_cast<double>(rand());
        result = QString::number(op_1 * op_2, 'f', calc.precision());

        test_exp = QString::number(op_1, 'f', calc.precision()) + "*" + QString::number(op_2, 'f', calc.precision());
        calc.calculate(test_exp, test_result);

        try
        {
            if(result != test_result)
            {
                ++failure_cnt;
                out << "Failure!\t\t" << test_exp << "\n";
            }
        }
        catch(StringMathError &err)
        {
            out << "Exception!\t\t" << test_exp << "\t\t" << err.what() << "\n";
        }

        ++check_num;
    }

    if(failure_cnt == 0)
        out << "There are no failures!\n\n";
    else
        out << "\nThere are " << failure_cnt << " failures!\n\n";
}

void div_rand_tests()
{
    int failure_cnt = 0;
    double op_1 = 0.;
    double op_2 = 0.;

    QString result = "";
    QString test_exp = "";
    QString test_result = "";

    StringMath calc;

    QTextStream out(stdout);
    out << "Division check...\n";

    srand(QTime::currentTime().msec());

    int check_num = 0;
    while(check_num < rand_checks_num)
    {
        op_1 = static_cast<double>(rand());
        op_2 = static_cast<double>(rand());
        result = QString::number(op_1 / op_2, 'f', calc.precision());

        test_exp = QString::number(op_1, 'f', calc.precision()) + "/" + QString::number(op_2, 'f', calc.precision());
        calc.calculate(test_exp, test_result);

        try
        {
            if(result != test_result)
            {
                ++failure_cnt;
                out << "Failure!\t\t" << test_exp << "\n";
            }
        }
        catch(StringMathError &err)
        {
            out << "Exception!\t\t" << test_exp << "\t\t" << err.what() << "\n";
        }

        ++check_num;
    }

    if(failure_cnt == 0)
        out << "There are no failures!\n\n";
    else
        out << "\nThere are " << failure_cnt << " failures!\n\n";
}

void file_tests()
{
    QTextStream out(stdout);
    out << "Tests from the specified file...\n";

    QFile f(file_name);
    if(f.open(QFile::ReadOnly))
    {
        int failure_cnt = 0;

        int test_prec = 0;        
        QString test_name = "";
        QString test_exp = "";
        QString test_res = "";
        QString calc_res = "";

        StringMath calc;

        QString line = "";
        QTextStream in(&f);
        while(in.readLineInto(&line))
        {
            if(line.isEmpty())
                continue;

            if(!test_str_parser(line, test_name, test_prec, test_exp, test_res))
            {
                out << "The test string parsing failure! \"" << line << "\"\n";
                continue;
            }

            try
            {                
                calc.set_precision(test_prec);
                calc.calculate(test_exp, calc_res);
                if(test_res != calc_res)
                {
                    ++failure_cnt;
                    out << "Failure!\t\t" << test_name << "\n";
                }
            }
            catch(StringMathError &err)
            {
                out << "Exception!\t\t" << test_name << "\t\t" << err.what() << "\n";
            }
        }

        if(failure_cnt == 0)
            out << "There are no failures!\n";
        else
            out << "\nThere are " << failure_cnt << " failures!\n";

        f.close();
    }
    else
        out << "Can't open the test file!\n";
}
