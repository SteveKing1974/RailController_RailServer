#include "speedcontroller.h"
#include "wiringPi.h"
#include "softPwm.h"

SpeedController::SpeedController(int in1, int in2, int pwm, int controllerID) :
    m_Direction(SpeedController::eSpeedBackward),
    m_Speed(0),
    m_In1(in1),
    m_In2(in2),
    m_PWM(pwm),
    m_ID(controllerID)
{
    pinMode(m_In1, OUTPUT);
    digitalWrite(m_In1, LOW);
    pinMode(m_In2, OUTPUT);
    digitalWrite(m_In2, LOW);
    softPwmCreate(m_PWM, 100, 100);
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

void SpeedController::setEnabled(bool newVal)
{
    if (newVal != m_Enabled)
    {
        m_Enabled = newVal;

        if (!m_Enabled)
        {
            setSpeed(0);
        }
    }
}



int SpeedController::id() const
{
    return m_ID;
}

