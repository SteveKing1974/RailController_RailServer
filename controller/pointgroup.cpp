#include "pointgroup.h"
#include "wiringPi.h"

PointGroup::PointGroup(BasePointController *pPoint1, BasePointController *pPoint2, int line1, int line2, PointDirection onDir) :
    BasePointController(pPoint1->direction()),
    m_pPoint1(pPoint1),
    m_pPoint2(pPoint2),
    m_Line1Switch(line1),
    m_Line2Switch(line2),
    m_OnDirection(onDir)
{
    digitalWrite (m_Line1Switch, HIGH);
    digitalWrite (m_Line2Switch, HIGH);
}

void PointGroup::setDirection(BasePointController::PointDirection dir)
{
    m_Direction = dir;

    if (dir == m_OnDirection)
    {
        digitalWrite (m_Line1Switch, LOW);
        digitalWrite (m_Line2Switch, LOW);
    }
    else
    {
        digitalWrite (m_Line1Switch, HIGH);
        digitalWrite (m_Line2Switch, HIGH);
    }
    m_pPoint1->setDirection(dir);
    m_pPoint2->setDirection(dir);
}

