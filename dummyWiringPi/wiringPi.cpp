#include <QDebug>

void wiringPiSetup ()
{
    qDebug() << "wiringPiSetup";
}

void pinMode (int, int)
{
    qDebug() << "pinMode";
}

void digitalWrite (int a, int b)
{
    qDebug() << "digitalWrite" << a << b;
}

void delay(int)
{
    qDebug() << "delay";
}

int  softPwmCreate (int pin, int value, int range)
{ return 0;}
void softPwmWrite  (int pin, int value)
{
    qDebug() << "PWM write" << pin << value;
}
void softPwmStop   (int pin) {}
