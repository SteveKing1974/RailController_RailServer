#include "testcommandhandler.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

TestCommandHandler::TestCommandHandler()
{

}

QByteArray TestCommandHandler::getCommand(const QByteArray &url) const
{
    QJsonObject obj;

    obj.insert("error", QString("Unknown command: " + url));

    return QJsonDocument(obj).toJson();
}

QByteArray TestCommandHandler::putCommand(const QByteArray &url, const QByteArray &data) const
{
    const QStringList splitPath = QString(url.toLower()).split('/', QString::SkipEmptyParts);

    QJsonObject obj;
    QJsonObject cmdData = fromPUTData(data);

    qDebug() << "Put" << splitPath << cmdData;

    if (splitPath[0]=="testcommand")
    {
        const QStringList command = cmdData.value("command").toString().split("+", QString::SkipEmptyParts);
        qDebug() << command;
        const QByteArray res = m_TestHandler.handleCommand(command);
        obj.insert("result", QString(res));
    }
    else
    {
        obj.insert("error", QString("Badly formed path: " + url));
    }

    return QJsonDocument(obj).toJson();
}

