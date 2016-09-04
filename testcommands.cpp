#include "testcommands.h"


#include "wiringPi.h"

TestCommands::TestCommands()
{

}

QByteArray TestCommands::handleCommand(const QList<QByteArray> &cmd) const
{
    if (cmd[0]=="set")
    {
        if (cmd.length()==3)
        {
            int lineVal = cmd[1].toInt();
            int onOff = cmd[2].toInt();

            digitalWrite(lineVal, onOff);
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

    return QByteArray("done");
}

