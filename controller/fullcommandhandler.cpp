#include "fullcommandhandler.h"

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
    const QList<QByteArray> keys = m_pPanel->allNodes();
    foreach (const QByteArray& key, keys)
    {
        nodes.insert(key, m_pPanel->getLightState(key));
    }

    QJsonObject points;
    const QList<QByteArray> allPoints = m_pController->allPoints();
    foreach (const QByteArray& point, allPoints)
    {
        QJsonObject pt;
        pt.insert("direction", m_pController->getPoint(point)->direction());
        pt.insert("enabled", m_pController->getPoint(point)->enabled());
        points.insert(point, pt);
    }
    obj.insert("nodes", nodes);
    obj.insert("points", points);

    return obj;
}

QJsonObject FullCommandHandler::getControllerData() const
{
    QJsonObject obj;

    foreach (const QByteArray& name, m_pController->allControllers())
    {
        SpeedController* pCtrl = m_pController->getController(name);

        QJsonObject control;
        control.insert("speed", pCtrl->speed());
        control.insert("direction", pCtrl->direction());
        control.insert("directionEnabled", pCtrl->speed()==0);
        control.insert("speedEnabled", pCtrl->enabled());

        obj.insert(name, control);
    }

    return obj;
}

QByteArray FullCommandHandler::getCommand(const QByteArray &url) const
{
    const QList<QByteArray> splitPath = url.toLower().split('/');

    QJsonObject obj;

    if (splitPath.length()>=3)
    {
        if (splitPath.at(2) == "panel")
        {
            obj = getPanelData();
        }
        else if (splitPath.at(2) == "controller")
        {
            obj = getControllerData();
        }
        else
        {
            obj.insert("error", QString("Unknown object: " + splitPath.at(2)));
        }
    }
    else
    {
        obj.insert("error", QString("Badly formed path: " + url));
    }

    return QJsonDocument(obj).toJson();
}

QByteArray FullCommandHandler::putCommand(const QByteArray &url, const QByteArray &data) const
{
    const QList<QByteArray> splitPath = url.toLower().split('/');

    QJsonObject obj;

    qDebug() << "Put" << splitPath;

    if (splitPath.length()>=3)
    {
        if (splitPath.at(2) == "panel")
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
                obj.insert("error", QString("Invalid point: " + splitPath.at(3)));
            }

        }
        else if (splitPath.at(2) == "controller")
        {
            if (splitPath.length()>=4)
            {
                SpeedController* pCtrl = m_pController->getController(splitPath.at(3));

                if (pCtrl != 0)
                {
                    QJsonObject dataObj = fromPUTData(data);

                    pCtrl->setDirection(static_cast<SpeedController::SpeedDirection>(dataObj.value("direction").toString().toInt()));
                    m_pInterlock->setSpeed(splitPath.at(3), dataObj.value("speed").toString().toInt());

                    obj = getControllerData();
                }
                else
                {
                    obj.insert("error", QString("Invalid controller: " + splitPath.at(3)));
                }
            }
            else
            {
                obj.insert("error", QString("Missing controller name"));
            }
        }
        else
        {
            obj.insert("error", QString("Unknown object: " + splitPath.at(2)));
        }
    }
    else
    {
        obj.insert("error", QString("Badly formed path: " + url));
    }

    return QJsonDocument(obj).toJson();
}


