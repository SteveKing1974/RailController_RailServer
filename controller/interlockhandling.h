#ifndef INTERLOCKHANDLING_H
#define INTERLOCKHANDLING_H

#include <QByteArray>
#include <QList>
#include "hardwarecontroller.h"
#include "basecontroller.h"

class InterlockHandling
{
public:
    InterlockHandling(HardwareController *pControl);

    void togglePoint(const QString &pointName);
    bool updateController(const QJsonObject& obj);

private:
    BaseController::ControllerState maskToState(quint8 mask) const;

    HardwareController* m_pController;
    bool isValidMask(quint8 mask) const;
    void updateEnabled();
};

#endif // INTERLOCKHANDLING_H
