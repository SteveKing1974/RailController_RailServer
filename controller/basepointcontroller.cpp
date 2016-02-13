#include "basepointcontroller.h"

BasePointController::BasePointController(PointDirection defaultDirection) :
    m_Direction(defaultDirection),
    m_Enabled(true)
{

}

void BasePointController::setDirection(BasePointController::PointDirection dir)
{
    m_Direction = dir;
}


BasePointController::PointDirection BasePointController::direction() const
{
    return m_Direction;
}

void BasePointController::toggle()
{
    if (m_Direction==ePointLeft)
    {
        setDirection(ePointRight);
    }
    else
    {
        setDirection(ePointLeft);
    }
}

bool BasePointController::enabled() const
{
    return m_Enabled;
}

void BasePointController::setEnabled(bool newVal)
{
    m_Enabled = newVal;
}
