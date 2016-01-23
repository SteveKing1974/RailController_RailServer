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
