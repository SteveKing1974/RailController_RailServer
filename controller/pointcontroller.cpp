#include "pointcontroller.h"

#include "wiringPi.h"

#include <QDebug>

PointController::PointController(int powerLine, int controlLine, PointDirection defaultDirection) :
    BasePointController(static_cast<PointDirection>(-1)),
    m_PowerLine(powerLine),
    m_ControlLine(controlLine)
{
    if (m_PowerLine>=0 && m_ControlLine>=0)
    {
        digitalWrite (m_PowerLine, HIGH);
        digitalWrite (m_ControlLine, HIGH);
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

    digitalWrite (m_ControlLine, val);
    delay (500);
    digitalWrite (m_PowerLine, LOW);
    delay(500);
    digitalWrite (m_PowerLine, HIGH);
}


