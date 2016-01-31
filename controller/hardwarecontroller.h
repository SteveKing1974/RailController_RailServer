#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include <QObject>
#include <QByteArray>
#include <QHash>
#include "basepointcontroller.h"
#include "speedcontroller.h"

class HardwareController : public QObject
{
    Q_OBJECT
public:
    explicit HardwareController(QObject *parent = 0);
    ~HardwareController();

    QList<QByteArray> allPoints() const;
    QList<QByteArray> allControllers() const;

    BasePointController* getPoint(const QByteArray& name) const;
    SpeedController* getController(const QByteArray& name) const;

signals:

public slots:

private:
    QHash<QByteArray, BasePointController*> m_Points;
    QHash<QByteArray, SpeedController*> m_Controllers;
};

#endif // HARDWARECONTROLLER_H
