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

    qDebug() << splitPath;

    return QByteArray("{\"speed\" : \"0\"}");
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


