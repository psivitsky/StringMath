//---------------------------------------------------------------------------------------------------------------------------------------------------
/*!
 * \brief
 * The "StringMath" test console application
 * \details
 * Create a text file in the application folder with test expressions such as "1+1=2".
 * Specify the expressions results with precision 'precision'.
 * After that run the application and see the test results in the console.
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------

#include    <QCoreApplication>

#include    <QFile>
#include    <QTextStream>

#include    "string_math.h"

static const int    precision = 1;

const QString file_name = "test.txt";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream out(stdout);

    QFile f(file_name);
    if(f.open(QFile::ReadOnly))
    {
        StringMath calc(precision);

        int failure_cnt = 0;
        QString line = "";
        QTextStream in(&f);
        while(in.readLineInto(&line))
        {
            if(line.isEmpty())
            {
                out << "\n";
                continue;
            }

            QString exp_str = line.mid(0, line.indexOf("="));        //The test expression.

            double res_val = line.mid(line.indexOf("=") + 1, line.size() - line.indexOf("=")).toDouble();        //The test etalon result.
            //Rounding of test etalon result to 'precision'...
            double res_int_part = static_cast<double>(qFloor(res_val));
            double res_nonint_part = res_val - qFloor(res_val);
            double prec_dec = qPow(10., precision);
            res_nonint_part = static_cast<double>(qRound(res_nonint_part * prec_dec)) / prec_dec;
            res_val = res_int_part + res_nonint_part;

            try
            {
                if(res_val == calc.string_process(exp_str))
                    out << "Success!\t" << line << "\n";
                else
                {
                    ++failure_cnt;
                    out << "Failure!\t" << line << "\n";
                }
            }
            catch(StringMathError &err)
            {
                out << "Exception!\t" << err.msg << "\n";
            }

        }

        if(failure_cnt == 0)
            out << "There are no failures!\n";
        else
            out << "There are " << failure_cnt << " failures!\n";

        f.close();
    }
    else
        out << "Can't open the test file!\n";

    return 0;
}
