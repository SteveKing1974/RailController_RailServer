#include "commandline.h"
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QRegExp>

#include <QDebug>

#include "wiringPi.h"

CommandLine::CommandLine(QObject *parent) : QObject(parent)
{

}

int CommandLine::run()
{
    QTextStream stream(stdin);
    QString line;
    do {
        line = stream.readLine();

        const QStringList cmd = line.split(QRegExp("\\s+"));

        if (!cmd.isEmpty())
        {
            if (cmd[0] == "quit")
            {
                return 0;
            }
            else if (cmd[0]=="set")
            {
                if (cmd.length()==3)
                {
                    int lineVal = cmd[1].toInt();
                    int onOff = cmd[2].toInt();

                    digitalWrite(lineVal, onOff);
                }
            }
            else if (cmd[0]=="test")
            {
                for (int i=0; i<48; ++i)
                {
                    pinMode (128 + i, OUTPUT) ;
                    digitalWrite(128 + i, 1);
                }
                for (int i=0; i<48; ++i)
                {
                    qDebug() << "Return to write to " << 128 +i;
                    stream.readLine();
                    digitalWrite(128 + i, 0);
                }
                qDebug() << "Done";
                stream.readLine();
                for (int i=0; i<48; ++i)
                {
                    digitalWrite(128 + i, 1);
                }
            }
            else if (cmd[0]=="toggleHigh")
            {
                if (cmd.length()==2)
                {
                    int lineVal = cmd[1].toInt();

                    digitalWrite(lineVal, 1);

                    delay(500);

                    digitalWrite(lineVal, 0);
                }
            }
            else if (cmd[0]=="toggleLow")
            {
                if (cmd.length()==2)
                {
                    int lineVal = cmd[1].toInt();

                    digitalWrite(lineVal, 1);

                    delay(500);

                    digitalWrite(lineVal, 0);
                }
            }
        }
    } while (!line.isNull());

    return 0;
}

