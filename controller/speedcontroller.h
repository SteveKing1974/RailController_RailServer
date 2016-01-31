#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H


class SpeedController
{
public:
    enum SpeedDirection {
        eSpeedForward,
        eSpeedBackward
    };

    SpeedController(int in1, int in2, int pwm, int controllerID);

    bool setDirection(SpeedDirection dir);
    SpeedDirection direction() const;

    bool setSpeed(int speed);
    int speed() const;

    bool enabled() const;
    void setEnabled(bool newVal);

    int id() const;

private:
    SpeedDirection m_Direction;
    int m_Speed;
    bool m_Enabled;

    const int m_In1;
    const int m_In2;
    const int m_PWM;
    const int m_ID;
};

#endif // SPEEDCONTROLLER_H
