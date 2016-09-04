#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QObject>
#include "testcommands.h"

class CommandLine : public QObject
{
    Q_OBJECT
public:
    explicit CommandLine(QObject *parent = 0);

    int run();
signals:

public slots:

private:
    TestCommands m_CommandHandler;
};

#endif // COMMANDLINE_H
