#ifndef INTERLOCKHANDLING_H
#define INTERLOCKHANDLING_H

#include <QByteArray>
#include <QList>
#include "hardwarecontroller.h"

class InterlockHandling
{
public:
    InterlockHandling(HardwareController *pControl);

    void togglePoint(const QString &pointName);
    void setSpeed(const QString &controller, int newSpeed);

private:
    HardwareController* m_pController;
    bool isValidMask(quint8 mask) const;
    void updateEnabled();
};

#endif // INTERLOCKHANDLING_H
