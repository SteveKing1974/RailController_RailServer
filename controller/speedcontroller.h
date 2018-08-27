#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H

#include "basecontroller.h"

class SpeedController : public BaseController
{
    Q_OBJECT

public:

    SpeedController(int in1, int in2, int pwm, int line1, int line2);

    int id() const;

private slots:
    void updateHW();


private:

    const int m_In1;
    const int m_In2;
    const int m_PWM;

    const int m_Line1Switch;
    const int m_Line2Switch;
};

#endif // SPEEDCONTROLLER_H
