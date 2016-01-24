#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "hardwarecontroller.h"

class CommandHandler
{
public:
    CommandHandler(HardwareController* pControl);

    QByteArray getCommand(const QByteArray& url) const;

    QByteArray putCommand(const QByteArray& url, const QByteArray& data) const;

private:
    HardwareController* m_pController;

    SpeedController *controllerFromUrl(const QByteArray &url, QJsonObject &obj) const;
};

#endif // COMMANDHANDLER_H
