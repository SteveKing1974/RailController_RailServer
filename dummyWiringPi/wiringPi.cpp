#include <QDebug>

#include <QHash>
#include <QSemaphore>

QHash<int,int> g_Table;
QSemaphore g_Sem(0);

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
    g_Table[a] = b;
    qDebug() << "digitalWrite" << g_Table;
}

void delay(int delayMs)
{
    g_Sem.tryAcquire(1, delayMs);
    qDebug() << "delay";
}

int  softPwmCreate (int pin, int value, int range)
{ return 0;}

void softPwmWrite  (int pin, int value)
{
    qDebug() << "PWM write" << pin << value;
}

void softPwmStop   (int pin) {}
