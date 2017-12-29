#include "testcommandhandler.h"

#include "jsonkeys.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

TestCommandHandler::TestCommandHandler()
{

}

QJsonObject TestCommandHandler::handleCommand(const QJsonObject& data)
{
    QJsonObject obj;

     obj.insert("command", QLatin1String(QJsonDocument(data).toJson()));

      return obj;
}

//QJsonObject TestCommandHandler::putCommand(const QByteArray &data) const
//{
//    const QStringList splitPath = QString(QLatin1String(data.toLower())).split('/', QString::SkipEmptyParts);

//    QJsonObject obj;
//    //QJsonObject cmdData = QJsonObject(data); //fromPUTData(data);

//    qDebug() << "Put" << splitPath; // << cmdData;

//    if (splitPath[0]=="testcommand")
//    {
//        const QStringList command; // = cmdData.value("command").toString().split("+", QString::SkipEmptyParts);
//        qDebug() << command;
//        const QByteArray res = m_TestHandler.handleCommand(command);
//        obj.insert("result", QLatin1String(res));
//    }
//    else
//    {
//        obj.insert(JsonKeys::error(), QLatin1String("Badly formed path: " + data));
//    }

//    return obj;
//}


