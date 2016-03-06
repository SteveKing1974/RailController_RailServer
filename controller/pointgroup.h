#ifndef POINTGROUP_H
#define POINTGROUP_H

#include "basepointcontroller.h"

class PointGroup : public BasePointController
{
public:
    PointGroup(BasePointController* pPoint1, BasePointController* pPoint2, int line1, int line2);

    void setDirection(PointDirection dir);

private:
    BasePointController* m_pPoint1;
    BasePointController* m_pPoint2;

    const int m_Line1Switch;
    const int m_Line2Switch;
};

#endif // POINTGROUP_H
