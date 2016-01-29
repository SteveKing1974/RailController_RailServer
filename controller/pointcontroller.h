#ifndef POINTCONTROLLER_H
#define POINTCONTROLLER_H

#include <QString>

class PointController
{
public:
    enum PointDirection {
        ePointLeft,
        ePointRight
    };

    PointController();
    PointController(int powerLine, int controlLine);

    void setDirection(PointController::PointDirection dir);
    PointController::PointDirection direction() const;

private:
    PointDirection m_Direction;
    const int m_PowerLine;
    const int m_ControlLine;
};

#endif // POINTCONTROLLER_H
