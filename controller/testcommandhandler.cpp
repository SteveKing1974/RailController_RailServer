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
    const QList<QByteArray> splitPath = url.toLower().split('/');

    QJsonObject obj;
    QJsonDocument cmdData = fromPUTData(data);

    qDebug() << "Put" << splitPath << cmdData;

    if (splitPath.length()>=3)
    {
        const QByteArray res = m_TestHandler.handleCommand(splitPath);
        obj.insert("result", QString(res));
    }
    else
    {
        obj.insert("error", QString("Badly formed path: " + url));
    }

    return QJsonDocument(obj).toJson();
}

