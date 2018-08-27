#include "speedcontroller.h"
#include "wiringPi.h"
#include "softPwm.h"

#include <QDebug>

#include "hardwarecontroller.h"

SpeedController::SpeedController(int in1, int in2, int pwm, int line1, int line2) :
    BaseController(0),
    m_In1(in1),
    m_In2(in2),
    m_PWM(pwm),
    m_Line1Switch(line1),
    m_Line2Switch(line2)
{
    pinMode(m_In1, OUTPUT);
    HardwareController::setLine(m_In1, LOW);
    pinMode(m_In2, OUTPUT);
    HardwareController::setLine(m_In2, LOW);

    connect(this, SIGNAL(controlValueChanged()), this, SLOT(updateHW()));
    connect(this, SIGNAL(stateChanged()), this, SLOT(updateHW()));
    connect(this, SIGNAL(controllerUpdatedFromJson()), this, SLOT(updateHW()));

    softPwmCreate(m_PWM, 100, 100);
    setState(CONTROLLER_OFF, true);
}


void SpeedController::updateHW()
{
    if (state() == CONTROLLER_ON)
    {
        HardwareController::setLine (m_Line1Switch, LOW);
        HardwareController::setLine (m_Line2Switch, LOW);
    }
    else
    {
        HardwareController::setLine (m_Line1Switch, HIGH);
        HardwareController::setLine (m_Line2Switch, HIGH);
    }

    if (controlValue()==0)
    {
        HardwareController::setLine(m_In1, LOW);
        HardwareController::setLine(m_In2, LOW);

        HardwareController::setLine(m_PWM, LOW);
        softPwmWrite(m_PWM, 100);
    }
    else
    {
        if (direction()==CONTROLLER_FORWARD)
        {
           HardwareController::setLine(m_In1, LOW);
           HardwareController::setLine(m_In2, HIGH);
        }
        else
        {
            HardwareController::setLine(m_In1, HIGH);
            HardwareController::setLine(m_In2, LOW);
        }

        softPwmWrite(m_PWM, controlValue());
    }
}

