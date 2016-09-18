#ifndef TESTCOMMANDS_H
#define TESTCOMMANDS_H

#include <QList>
#include <QByteArray>
#include <QStringList>

class TestCommands
{
public:
    TestCommands();

    QByteArray handleCommand(const QStringList &cmd) const;
};

#endif // TESTCOMMANDS_H
