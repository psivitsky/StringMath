//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * The "StringMath" test console application
 * \details
 * Create a text file in the application folder with test expressions.
 * The test syntax is as follows: |test_name,expression_str=calc_result|
 * Specify the expressions results with precision 'precision'.
 * After that run the application and see the test results in the terminal.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------

#include    <QCoreApplication>

#include    <QFile>
#include    <QTextStream>

#include    "string_math.h"

static const int    precision = 1;

bool    test_str_parser(const QString &testStr, QString &testName, QString &testExp, double &testRes);

const QString file_name = "test.txt";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream out(stdout);

    QFile f(file_name);
    if(f.open(QFile::ReadOnly))
    {
        int failure_cnt = 0;

        double test_res = 0.;
        QString test_name = "";
        QString test_exp = "";

        StringMath calc(precision);

        QString line = "";
        QTextStream in(&f);
        while(in.readLineInto(&line))
        {
            if(line.isEmpty())
                continue;

            if(!test_str_parser(line, test_name, test_exp, test_res))
            {
                out << "The test string parsing failure! \"" << line << "\"\n";
                continue;
            }

            try
            {
                if(test_res != calc.string_process(test_exp))
                {
                    ++failure_cnt;
                    out << "Failure!\t\t" << test_name << "\n";
                }
            }
            catch(StringMathError &err)
            {
                out << "Exception!\t\t" << test_name << "\t\t" << err.msg << "\n";
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

    return 0;
}

bool test_str_parser(const QString &testStr, QString &testName, QString &testExp, double &testRes)
{
    testName = "";
    testExp = "";

    QRegExp test_str_checker("^\\|\\w+\\,[^=]+\\=[^|]+\\|$");

    if(!test_str_checker.exactMatch(testStr))
        return false;

    testName = testStr.mid(testStr.indexOf("|") + 1, testStr.indexOf("," - testStr.indexOf("|")) - 1);
    testExp = testStr.mid(testStr.indexOf(",") + 1, testStr.indexOf("=") - testStr.indexOf(",") - 1);
    testRes = testStr.mid(testStr.indexOf("=") + 1, testStr.lastIndexOf("|") - testStr.indexOf("=") - 1).toDouble();

    double test_res_int_part = static_cast<double>(floor(testRes));
    double test_res_nonint_part = testRes - floor(testRes);
    double prec_dec = pow(10., precision);
    test_res_nonint_part = static_cast<double>(qRound(test_res_nonint_part * prec_dec)) / prec_dec;
    testRes = test_res_int_part + test_res_nonint_part;

    return true;
}
