#include "commandhandler.h"
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

CommandHandler::CommandHandler(HardwareController *pControl) :
    m_pController(pControl)
{
}

QByteArray CommandHandler::getCommand(const QByteArray &url)
{
    const QList<QByteArray> splitPath = url.split('/');

    QJsonObject obj;

    if (splitPath.length()>2)
    {
        const SpeedController* pCtrl = m_pController->getController(splitPath.at(2));

        if (pCtrl != 0)
        {
            obj.insert("speed", pCtrl->speed());
            obj.insert("direction", pCtrl->direction());
            obj.insert("directionEnabled", pCtrl->speed()==0);
            obj.insert("speedEnabled", true);
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

    return QJsonDocument(obj).toJson();
}

QByteArray CommandHandler::putCommand(const QByteArray &url, const QByteArray &data)
{
    QByteArray copyOfCommand = data;
    copyOfCommand.replace("=", "\": \"");
    copyOfCommand.replace("&", "\" , \"");
    copyOfCommand.push_front("{ \"");
    copyOfCommand.push_back("\" }");
    QJsonDocument doc = QJsonDocument::fromJson(copyOfCommand);

    qDebug() << doc.toJson() << url;
    return QByteArray("{\"data\" : \"2\"}");
}


