#ifndef INTERLOCKHANDLING_H
#define INTERLOCKHANDLING_H

#include <QByteArray>
#include <QList>

class InterlockHandling
{
public:
    InterlockHandling();

    void togglePoint(const QByteArray& point);
    void setSpeed(const QByteArray& controller, int value);

private:
    QList<QByteArray> m_DontCarePoints;


};

#endif // INTERLOCKHANDLING_H
