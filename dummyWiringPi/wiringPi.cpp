#include <QDebug>

void wiringPiSetup ()
{
    qDebug() << "wiringPiSetup";
}

void pinMode (int, int)
{
    qDebug() << "pinMode";
}

void digitalWrite (int, int)
{
    qDebug() << "digitalWrite";
}

void delay(int)
{
    qDebug() << "delay";
}

int  softPwmCreate (int pin, int value, int range)
{ return 0;}
void softPwmWrite  (int pin, int value) {}
void softPwmStop   (int pin) {}
