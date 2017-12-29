#include "commandhandler.h"
#include "jsonkeys.h"

#include <QJsonDocument>
#include <QDebug>

void CommandHandler::receiveData(const QByteArray &data)
{
    QJsonParseError err;
    QJsonObject obj = QJsonDocument::fromJson(data, &err).object();

    if (err.error == QJsonParseError::NoError )
    {
        qDebug() << "Got" << obj.keys();
        obj = handleCommand(obj);
    }
    else
    {
        obj.insert(JsonKeys::error(), err.errorString());
    }


   emit sendData(QJsonDocument(obj).toJson());
}
