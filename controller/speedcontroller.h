#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H


class SpeedController
{
public:
    enum SpeedDirection {
        eSpeedForward,
        eSpeedBackward
    };

    SpeedController(int in1, int in2, int pwm);

    bool setDirection(SpeedDirection dir);
    SpeedDirection direction() const;

    bool setSpeed(int speed);
    int speed() const;

private:
    SpeedDirection m_Direction;
    int m_Speed;

    const int m_In1;
    const int m_In2;
    const int m_PWM;
};

#endif // SPEEDCONTROLLER_H
