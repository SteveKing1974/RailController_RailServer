#include "commandline.h"
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QRegExp>

#include <QDebug>


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

        if (cmd[0] == "quit")
        {
            return 0;
        }
        else if (!cmd.isEmpty())
        {
            QList<QByteArray> byteCmds;
            foreach (const QString& str, cmd)
            {
                byteCmds.push_back(str.toLatin1());
            }

            qDebug() << m_CommandHandler.handleCommand(byteCmds);
        }

    } while (!line.isNull());

    return 0;
}

