#include "pointgroup.h"

PointGroup::PointGroup(BasePointController *pPoint1, BasePointController *pPoint2) :
    BasePointController(pPoint1->direction()),
    m_pPoint1(pPoint1),
    m_pPoint2(pPoint2)
{

}

void PointGroup::setDirection(BasePointController::PointDirection dir)
{
    m_Direction = dir;
    m_pPoint1->setDirection(dir);
    m_pPoint2->setDirection(dir);
}

