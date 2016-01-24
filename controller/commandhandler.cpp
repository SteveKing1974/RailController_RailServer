#include "commandhandler.h"
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

CommandHandler::CommandHandler(HardwareController *pControl) :
    m_pController(pControl)
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
    QJsonObject obj;

    const SpeedController* pCtrl = controllerFromUrl(url, obj);

    if (pCtrl != 0)
    {
        obj.insert("speed", pCtrl->speed());
        obj.insert("direction", pCtrl->direction());
        obj.insert("directionEnabled", pCtrl->speed()==0);
        obj.insert("speedEnabled", true);
    }

    return QJsonDocument(obj).toJson();
}

QByteArray CommandHandler::putCommand(const QByteArray &url, const QByteArray &data) const
{
    QJsonObject obj;

    SpeedController* pCtrl = controllerFromUrl(url, obj);

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

    qDebug() << QJsonDocument(obj).toJson();
    return QJsonDocument(obj).toJson();
}


