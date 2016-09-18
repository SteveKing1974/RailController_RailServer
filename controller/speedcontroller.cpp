#include "speedcontroller.h"
#include "wiringPi.h"
#include "softPwm.h"

#include <QDebug>

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
    digitalWrite(m_In1, LOW);
    pinMode(m_In2, OUTPUT);
    digitalWrite(m_In2, LOW);

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
            digitalWrite(m_In1, LOW);
            digitalWrite(m_In2, LOW);

            digitalWrite(m_PWM, LOW);
            softPwmWrite(m_PWM, 100);
        }
        else
        {
            if (m_Direction==eSpeedForward)
            {
               digitalWrite(m_In1, LOW);
               digitalWrite(m_In2, HIGH);
            }
            else
            {
                digitalWrite(m_In1, HIGH);
                digitalWrite(m_In2, LOW);
            }

            softPwmWrite(m_PWM, m_Speed);
            qDebug() << "setting" << m_Speed;
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
    if (force || (newVal != m_Enabled))
    {
        qDebug() << "Set enabled" << newVal;
        m_Enabled = newVal;

        setSpeed(0);

        if (m_Enabled)
        {
            digitalWrite (m_Line1Switch, LOW);
            digitalWrite (m_Line2Switch, LOW);
        }
        else
        {
            digitalWrite (m_Line1Switch, HIGH);
            digitalWrite (m_Line2Switch, HIGH);
        }
    }
}



int SpeedController::id() const
{
    return m_ID;
}

