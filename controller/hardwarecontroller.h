#ifndef HARDWARECONTROLLER_H
#define HARDWARECONTROLLER_H

#include <QObject>
#include <QString>
#include <QHash>
#include "basepointcontroller.h"
#include "speedcontroller.h"
#include "isolatorcontroller.h"

class HardwareController : public QObject
{
    Q_OBJECT
public:
    explicit HardwareController(QObject *parent = 0);
    ~HardwareController();

    QList<QString> allPoints() const;
    QList<QString> allControllers() const;
    QList<QString> allIsolators() const;

    BasePointController* getPoint(const QString& name) const;
    SpeedController* getController(const QString& name) const;
    IsolatorController* getIsolator(const QString& name) const;

    static void setLine(int lineID, int value);

signals:

public slots:

private:
    QHash<QString, BasePointController*> m_Points;
    QHash<QString, SpeedController*> m_Controllers;
    QHash<QString, IsolatorController*> m_Isolators;
};

#endif // HARDWARECONTROLLER_H
