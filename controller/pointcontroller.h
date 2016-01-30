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
    PointController(int powerLine, int controlLine, PointDirection defaultDirection = ePointLeft);

    void setDirection(PointController::PointDirection dir);
    PointController::PointDirection direction() const;
    void toggle();

private:
    PointDirection m_Direction;
    const int m_PowerLine;
    const int m_ControlLine;
};

#endif // POINTCONTROLLER_H
