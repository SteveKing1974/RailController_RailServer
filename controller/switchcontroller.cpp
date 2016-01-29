#include "switchcontroller.h"

SwitchController::SwitchController() :
    m_State(eSwitchOpen)
{

}

void SwitchController::setState(SwitchController::SwitchState dir)
{
    m_State = dir;
}

SwitchController::SwitchState SwitchController::state() const
{
    return m_State;
}

