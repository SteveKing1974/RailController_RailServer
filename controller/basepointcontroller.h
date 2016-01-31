#ifndef BASEPOINTCONTROLLER_H
#define BASEPOINTCONTROLLER_H


class BasePointController
{
public:
    enum PointDirection {
        ePointLeft,
        ePointRight
    };

    BasePointController(PointDirection defaultDirection = ePointLeft);

    virtual void setDirection(PointDirection dir);

    PointDirection direction() const;
    void toggle();

protected:
    PointDirection m_Direction;
};

#endif // BASEPOINTCONTROLLER_H
