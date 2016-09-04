#ifndef TESTCOMMANDHANDLER_H
#define TESTCOMMANDHANDLER_H

#include "commandhandler.h"

#include "testcommands.h"
#include <QByteArray>

class TestCommandHandler : public CommandHandler
{
public:
    TestCommandHandler();

    QByteArray getCommand(const QByteArray& url) const;
    QByteArray putCommand(const QByteArray& url, const QByteArray& data) const;

private:
    TestCommands m_TestHandler;
};

#endif // TESTCOMMANDHANDLER_H
