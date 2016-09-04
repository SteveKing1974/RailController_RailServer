#ifndef TESTCOMMANDS_H
#define TESTCOMMANDS_H

#include <QList>
#include <QByteArray>

class TestCommands
{
public:
    TestCommands();

    QByteArray handleCommand(const QList<QByteArray>& cmd) const;
};

#endif // TESTCOMMANDS_H
