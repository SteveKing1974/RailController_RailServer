#include "pointgroup.h"

PointGroup::PointGroup(BasePointController *pPoint1, BasePointController *pPoint2, int line1, int line2) :
    BasePointController(pPoint1->direction()),
    m_pPoint1(pPoint1),
    m_pPoint2(pPoint2),
    m_Line1Switch(line1),
    m_Line2Switch(line2)
{

}

void PointGroup::setDirection(BasePointController::PointDirection dir)
{
    m_Direction = dir;
    m_pPoint1->setDirection(dir);
    m_pPoint2->setDirection(dir);
}

