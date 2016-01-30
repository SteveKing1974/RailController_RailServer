#include "commandhandler.h"
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

CommandHandler::CommandHandler(HardwareController *pControl, PanelBoard* pPanel) :
    m_pController(pControl),
    m_pPanel(pPanel)
{
}

SpeedController* CommandHandler::controllerFromUrl(const QByteArray& url, QJsonObject& obj) const
{
    const QList<QByteArray> splitPath = url.split('/');

    if (splitPath.length()>2)
    {
        SpeedController* pCtrl = m_pController->getController(splitPath.at(2));

        if (pCtrl != 0)
        {
            return pCtrl;
        }
        else
        {
            obj.insert("error", QString("Invalid controller: " + splitPath.at(2)));
        }
    }
    else
    {
        obj.insert("error", QString("Badly formed path: " + url));
    }

    return 0;
}

QByteArray CommandHandler::getCommand(const QByteArray &url) const
{
    const QList<QByteArray> splitPath = url.toLower().split('/');

    QJsonObject obj;

    if (splitPath.length()>=3)
    {
        if (splitPath.at(2) == "panel")
        {
            const QList<QByteArray> keys = m_pPanel->allNodes();
            foreach (const QByteArray& key, keys)
            {
                obj.insert(key, m_pPanel->getLightState(key));
            }

        }
        else if (splitPath.at(2) == "controller")
        {
            if (splitPath.length()>=4)
            {
                SpeedController* pCtrl = m_pController->getController(splitPath.at(3));

                if (pCtrl != 0)
                {
                    obj.insert("speed", pCtrl->speed());
                    obj.insert("direction", pCtrl->direction());
                    obj.insert("directionEnabled", pCtrl->speed()==0);
                    obj.insert("speedEnabled", true);
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

QByteArray CommandHandler::putCommand(const QByteArray &url, const QByteArray &data) const
{
    const QList<QByteArray> splitPath = url.toLower().split('/');

    QJsonObject obj;

    qDebug() << "Put" << splitPath;

    if (splitPath.length()>=3)
    {
        if (splitPath.at(2) == "panel")
        {
            PointController* pPoint = m_pController->getPoint(splitPath.at(3));
            if (pPoint)
            {
                pPoint->toggle();
                m_pPanel->refresh();
                const QList<QByteArray> keys = m_pPanel->allNodes();
                foreach (const QByteArray& key, keys)
                {
                    obj.insert(key, m_pPanel->getLightState(key));
                }
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
                    QByteArray copyOfCommand = data;
                    copyOfCommand.replace("=", "\": \"");
                    copyOfCommand.replace("&", "\" , \"");
                    copyOfCommand.push_front("{ \"");
                    copyOfCommand.push_back("\" }");
                    QJsonDocument doc = QJsonDocument::fromJson(copyOfCommand);

                    qDebug() << doc.toJson() << doc.object().value("speed").toString().toInt();
                    pCtrl->setSpeed(doc.object().value("speed").toString().toInt());
                    pCtrl->setDirection(static_cast<SpeedController::SpeedDirection>(doc.object().value("direction").toString().toInt()));


                    obj.insert("speed", pCtrl->speed());
                    obj.insert("direction", pCtrl->direction());
                    obj.insert("directionEnabled", pCtrl->speed()==0);
                    obj.insert("speedEnabled", true);
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


