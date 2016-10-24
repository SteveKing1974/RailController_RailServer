#include "isolatorcontroller.h"

#include "hardwarecontroller.h"
#include "wiringPi.h"

IsolatorController::IsolatorController(int controlLine) : m_ControlLine(controlLine), m_State(ISOLATED)
{
    setState(ISOLATED);
}

void IsolatorController::setState(IsolatorController::State newVal)
{
    m_State = newVal;
    if (newVal == ISOLATED)
    {
        HardwareController::setLine (m_ControlLine, HIGH);
    }
    else
    {
        HardwareController::setLine (m_ControlLine, LOW);
    }
}

void IsolatorController::toggle()
{
    if (m_State == ISOLATED)
    {
        setState(CONNECTED);
    }
    else
    {
        setState(ISOLATED);
    }
}

