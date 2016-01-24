#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "hardwarecontroller.h"

class CommandHandler
{
public:
    CommandHandler(HardwareController* pControl);

    QByteArray getCommand(const QByteArray& url);

    QByteArray putCommand(const QByteArray& url, const QByteArray& data);

private:
    HardwareController* m_pController;
};

#endif // COMMANDHANDLER_H
