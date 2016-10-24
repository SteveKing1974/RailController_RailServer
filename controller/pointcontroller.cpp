#include "pointcontroller.h"

#include "wiringPi.h"

#include <QDebug>
#include "hardwarecontroller.h"

PointController::PointController(int powerLine, int controlLine, PointDirection defaultDirection) :
    BasePointController(static_cast<PointDirection>(-1)),
    m_PowerLine(powerLine),
    m_ControlLine(controlLine)
{
    if (m_PowerLine>=0 && m_ControlLine>=0)
    {
        HardwareController::setLine (m_PowerLine, HIGH);
        HardwareController::setLine (m_ControlLine, HIGH);
    }

    setDirection(defaultDirection);
}

void PointController::setDirection(PointController::PointDirection dir)
{
    if (m_PowerLine<0 || m_ControlLine<0)
    {
        return;
    }

    m_Direction = dir;

    const int val = (dir == ePointLeft) ? HIGH : LOW;

    HardwareController::setLine (m_ControlLine, val);
    delay (500);
    HardwareController::setLine (m_PowerLine, LOW);
    delay(500);
    HardwareController::setLine (m_PowerLine, HIGH);
}


