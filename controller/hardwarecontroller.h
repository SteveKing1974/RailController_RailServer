#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include <QObject>
#include <QStringList>
#include <QHash>
#include "pointcontroller.h"
#include "speedcontroller.h"

class HardwareController : public QObject
{
    Q_OBJECT
public:
    explicit HardwareController(QObject *parent = 0);
    ~HardwareController();

    QStringList allPoints() const;
    QStringList allControllers() const;

    PointController* getPoint(const QString& name) const;
    SpeedController* getController(const QString& name) const;

signals:

public slots:

private:
    QHash<QString, PointController*> m_Points;
    QHash<QString, SpeedController*> m_Controllers;
};

#endif // HARDWARECONTROLLER_H
