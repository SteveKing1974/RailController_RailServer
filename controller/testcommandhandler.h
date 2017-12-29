#ifndef TESTCOMMANDHANDLER_H
#define TESTCOMMANDHANDLER_H

#include "commandhandler.h"

#include "testcommands.h"
#include <QByteArray>

class TestCommandHandler : public CommandHandler
{
public:
    TestCommandHandler();

    QJsonObject handleCommand(const QJsonObject& data);


private:
    TestCommands m_TestHandler;
};

#endif // TESTCOMMANDHANDLER_H
