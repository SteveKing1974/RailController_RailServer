#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "hardwarecontroller.h"
#include "panelboard.h"
#include "interlockhandling.h"

class CommandHandler
{
public:
    CommandHandler(HardwareController* pControl, PanelBoard *pPanel, InterlockHandling* pInterlock);

    QByteArray getCommand(const QByteArray& url) const;

    QByteArray putCommand(const QByteArray& url, const QByteArray& data) const;

private:
    HardwareController* m_pController;
    PanelBoard* m_pPanel;
    InterlockHandling* m_pInterlock;
};

#endif // COMMANDHANDLER_H
