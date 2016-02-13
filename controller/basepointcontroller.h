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

    bool enabled() const;
    void setEnabled(bool newVal);
protected:
    PointDirection m_Direction;
    bool m_Enabled;
};

#endif // BASEPOINTCONTROLLER_H
