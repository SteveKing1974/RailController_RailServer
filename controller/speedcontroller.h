#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H


class SpeedController
{
public:
    enum SpeedDirection {
        eSpeedForward,
        eSpeedBackward
    };

    SpeedController();

    bool setDirection(SpeedDirection dir);
    SpeedDirection direction() const;

    bool setSpeed(int speed);
    int speed() const;

private:
    SpeedDirection m_Direction;
    int m_Speed;
};

#endif // SPEEDCONTROLLER_H
