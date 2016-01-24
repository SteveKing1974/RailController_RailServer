#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include <QObject>
#include <QByteArray>
#include <QHash>
#include "pointcontroller.h"
#include "speedcontroller.h"

class HardwareController : public QObject
{
    Q_OBJECT
public:
    explicit HardwareController(QObject *parent = 0);
    ~HardwareController();

    QList<QByteArray> allPoints() const;
    QList<QByteArray> allControllers() const;

    PointController* getPoint(const QByteArray& name) const;
    SpeedController* getController(const QByteArray& name) const;

signals:

public slots:

private:
    QHash<QByteArray, PointController*> m_Points;
    QHash<QByteArray, SpeedController*> m_Controllers;
};

#endif // HARDWARECONTROLLER_H
