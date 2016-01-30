#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "hardwarecontroller.h"
#include "panelboard.h"

class CommandHandler
{
public:
    CommandHandler(HardwareController* pControl, PanelBoard *pPanel);

    QByteArray getCommand(const QByteArray& url) const;

    QByteArray putCommand(const QByteArray& url, const QByteArray& data) const;

private:
    HardwareController* m_pController;
    PanelBoard* m_pPanel;

    SpeedController *controllerFromUrl(const QByteArray &url, QJsonObject &obj) const;
};

#endif // COMMANDHANDLER_H
