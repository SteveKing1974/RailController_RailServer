#include "fullcommandhandler.h"
#include "jsonkeys.h"

#include <QJsonDocument>

#include <QDebug>

FullCommandHandler::FullCommandHandler(HardwareController *pControl, PanelBoard* pPanel, InterlockHandling *pInterlock) :
    m_pController(pControl),
    m_pPanel(pPanel),
    m_pInterlock(pInterlock)
{
}

QJsonObject FullCommandHandler::getPanelData() const
{
    QJsonObject obj;
    QJsonObject nodes;
    const QList<QString> keys = m_pPanel->allNodes();
    foreach (const QString& key, keys)
    {
        nodes.insert(key, m_pPanel->getLightState(key));
    }

    QJsonObject points;
    const QList<QString> allPoints = m_pController->allPoints();
    foreach (const QString& point, allPoints)
    {
        QJsonObject pt;
        pt.insert(JsonKeys::direction(), m_pController->getPoint(point)->direction());
        pt.insert(JsonKeys::enabled(), m_pController->getPoint(point)->enabled());
        points.insert(point, pt);
    }

    QJsonObject isolators;
    const QList<QString> allIsolators = m_pController->allIsolators();
    foreach (const QString& isolator, allIsolators)
    {
        QJsonObject iso;
        iso.insert(JsonKeys::enabled(), m_pController->getIsolator(isolator)->getState());
        isolators.insert(isolator, iso);
    }

    obj.insert(JsonKeys::nodes(), nodes);
    obj.insert(JsonKeys::points(), points);
    obj.insert(JsonKeys::isolators(), isolators);

    return obj;
}

QJsonObject FullCommandHandler::getControllerData() const
{
    QJsonObject obj;

    foreach (const QString& name, m_pController->allControllers())
    {
        SpeedController* pCtrl = m_pController->getController(name);

        QJsonObject control;
        control.insert(JsonKeys::speed(), pCtrl->speed());
        control.insert(JsonKeys::direction(), pCtrl->direction());
        control.insert(JsonKeys::directionEnabled(), pCtrl->speed()==0);
        control.insert(JsonKeys::speedEnabled(), pCtrl->enabled());

        obj.insert(name, control);
    }

    return obj;
}

QJsonObject FullCommandHandler::getCommand(const QByteArray& data) const
{
    const QString lowData = QLatin1String(data.toLower());

    QJsonObject obj;

    if (lowData == JsonKeys::panel())
    {
        obj.insert(JsonKeys::panel(), getPanelData());
    }
    else if (lowData == JsonKeys::controller())
    {
        obj.insert(JsonKeys::controller(), getControllerData());
    }
    else
    {
        obj.insert(JsonKeys::error(), QLatin1String("Badly formed data: " + data));
    }

    return obj;
}

QJsonObject FullCommandHandler::putCommand(const QByteArray& data) const
{
    const QList<QString> splitPath = QString(QLatin1String(data)).toLower().split('/');

    QJsonObject obj;

    qDebug() << "Put" << splitPath;

    if (splitPath.length()>=3)
    {
        if (splitPath.at(2) == JsonKeys::panel())
        {
            BasePointController* pPoint = m_pController->getPoint(splitPath.at(3));
            if (pPoint)
            {
                m_pInterlock->togglePoint(splitPath.at(3));
                m_pPanel->refresh();

                obj = getPanelData();
            }
            else
            {
                IsolatorController *pIsol = m_pController->getIsolator(splitPath.at(3));
                if (pIsol)
                {
                    pIsol->toggle();
                    m_pPanel->refresh();

                    obj = getPanelData();
                }
                else
                {
                    obj.insert(JsonKeys::error(), QString("Invalid point or isolator: " + splitPath.at(3)));
                }
            }

        }
        else if (splitPath.at(2) == JsonKeys::controller())
        {
            if (splitPath.length()>=4)
            {
                SpeedController* pCtrl = m_pController->getController(splitPath.at(3));

                if (pCtrl != 0)
                {
                    QJsonObject dataObj; // = fromPUTData(data);

                    pCtrl->setDirection(static_cast<SpeedController::SpeedDirection>(dataObj.value(JsonKeys::direction()).toString().toInt()));
                    m_pInterlock->setSpeed(splitPath.at(3), dataObj.value(JsonKeys::speed()).toString().toInt());

                    obj = getControllerData();
                }
                else
                {
                    obj.insert(JsonKeys::error(), QString("Invalid controller: " + splitPath.at(3)));
                }
            }
            else
            {
                obj.insert(JsonKeys::error(), QString("Missing controller name"));
            }
        }
        else
        {
            obj.insert(JsonKeys::error(), QString("Unknown object: " + splitPath.at(2)));
        }
    }
    else
    {
        obj.insert(JsonKeys::error(), QLatin1String("Badly formed path: " + data));
    }

    return obj;
}


