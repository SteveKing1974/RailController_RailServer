#include "speedcontroller.h"
#include "wiringPi.h"
#include "softPwm.h"

#include <QDebug>

#include "hardwarecontroller.h"

SpeedController::SpeedController(int in1, int in2, int pwm, int controllerID, int line1, int line2) :
    m_Direction(SpeedController::eSpeedBackward),
    m_Speed(0),
    m_In1(in1),
    m_In2(in2),
    m_PWM(pwm),
    m_ID(controllerID),
    m_Line1Switch(line1),
    m_Line2Switch(line2)
{
    pinMode(m_In1, OUTPUT);
    HardwareController::setLine(m_In1, LOW);
    pinMode(m_In2, OUTPUT);
    HardwareController::setLine(m_In2, LOW);

    softPwmCreate(m_PWM, 100, 100);
    setEnabled(false, true);
}

bool SpeedController::setDirection(SpeedController::SpeedDirection dir)
{
    if (m_Speed!=0)
    {
        return false;
    }

    if (dir!=m_Direction)
    {
        // Change direction, don't set HW as we're in stop
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
    qDebug() << "Set speed" << this << m_Speed;

    if (speed<0 || speed >100 || !m_Enabled)
    {
        return false;
    }

    if (speed != m_Speed)
    {
        // Set speed
        m_Speed = speed;

        if (m_Speed==0)
        {
            HardwareController::setLine(m_In1, LOW);
            HardwareController::setLine(m_In2, LOW);

            HardwareController::setLine(m_PWM, LOW);
            softPwmWrite(m_PWM, 100);
        }
        else
        {
            if (m_Direction==eSpeedForward)
            {
               HardwareController::setLine(m_In1, LOW);
               HardwareController::setLine(m_In2, HIGH);
            }
            else
            {
                HardwareController::setLine(m_In1, HIGH);
                HardwareController::setLine(m_In2, LOW);
            }

            softPwmWrite(m_PWM, m_Speed);
        }
    }

    return true;
}

int SpeedController::speed() const
{
    return m_Speed;
}

bool SpeedController::enabled() const
{
    return m_Enabled;
}

void SpeedController::setEnabled(bool newVal, bool force)
{
    qDebug() << "Set enabled" << this << newVal;

    if (force || (newVal != m_Enabled))
    {
        m_Enabled = newVal;

        setSpeed(0);

        if (m_Enabled)
        {
            HardwareController::setLine (m_Line1Switch, LOW);
            HardwareController::setLine (m_Line2Switch, LOW);
        }
        else
        {
            HardwareController::setLine (m_Line1Switch, HIGH);
            HardwareController::setLine (m_Line2Switch, HIGH);
        }
    }
}



int SpeedController::id() const
{
    return m_ID;
}

