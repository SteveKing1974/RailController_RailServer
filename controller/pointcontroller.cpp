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
        pinMode (m_PowerLine, OUTPUT) ;
        digitalWrite (m_PowerLine, HIGH);

        pinMode (m_ControlLine, OUTPUT) ;
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
    qDebug() << "Set control:" << val;
    digitalWrite (m_ControlLine, val);
    delay (500);
    qDebug() << "Set power low";
    digitalWrite (m_PowerLine, LOW);
    delay(500);
    qDebug() << "Set power high";
    digitalWrite (m_PowerLine, HIGH);
}


