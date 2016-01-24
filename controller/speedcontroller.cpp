#include "speedcontroller.h"

SpeedController::SpeedController() :
    m_Direction(SpeedController::eSpeedBackward),
    m_Speed(0)
{

}

bool SpeedController::setDirection(SpeedController::SpeedDirection dir)
{
    if (m_Speed!=0)
    {
        return false;
    }

    if (dir!=m_Direction)
    {
        // Change direction
        m_Direction = dir;
    }

    return true;
}

SpeedController::SpeedDirection SpeedController::direction() const
{
    return m_Direction;
}

bool SpeedController::setSpeed(int speed)
{
    if (speed<0 || speed >100)
    {
        return false;
    }

    if (speed != m_Speed)
    {
        // Set speed
        m_Speed = speed;
    }

    return true;
}

int SpeedController::speed() const
{
    return m_Speed;
}

