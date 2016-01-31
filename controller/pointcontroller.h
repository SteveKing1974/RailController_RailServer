#ifndef POINTCONTROLLER_H
#define POINTCONTROLLER_H

#include <QString>
#include "basepointcontroller.h"

class PointController : public BasePointController
{
public:
    PointController(int powerLine = -1, int controlLine = -1, PointDirection defaultDirection = ePointLeft);

    void setDirection(PointController::PointDirection dir);

private:
    const int m_PowerLine;
    const int m_ControlLine;
};

#endif // POINTCONTROLLER_H
