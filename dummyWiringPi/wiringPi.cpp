#include <QDebug>

#include <QHash>
#include <QSemaphore>

QHash<int,int> g_Table;
QSemaphore g_Sem(0);

#define DEBUG_WIRING    0

void wiringPiSetup ()
{
#if DEBUG_WIRING
    qDebug() << "wiringPiSetup";
#endif
}

void pinMode (int, int)
{
#if DEBUG_WIRING
    qDebug() << "pinMode";
#endif
}

void digitalWrite (int a, int b)
{
    g_Table[a] = b;
#if DEBUG_WIRING
    qDebug() << "digitalWrite" << g_Table;
#endif
}

void delay(int delayMs)
{
    g_Sem.tryAcquire(1, delayMs/10);
#if DEBUG_WIRING
    qDebug() << "delay";
#endif
}

int  softPwmCreate (int pin, int value, int range)
{
    return 0;
}

void softPwmWrite  (int pin, int value)
{
#if DEBUG_WIRING
    qDebug() << "PWM write" << pin << value;
#endif
}

void softPwmStop   (int pin)
{

}
