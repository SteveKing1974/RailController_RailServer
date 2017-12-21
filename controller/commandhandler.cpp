#include "commandhandler.h"
#include "jsonkeys.h"

#include <QJsonDocument>

void CommandHandler::receiveData(const QByteArray &data)
{
    QJsonObject obj;

    const QList<QByteArray> splitData = data.toLower().split(JsonKeys::seperator().toLatin1());
    if (splitData.length()==2)
    {
        if (splitData.at(0)==JsonKeys::get().toLatin1())
        {
            obj = getCommand(splitData.at(1));
        }
        else if (splitData.at(0)==JsonKeys::put().toLatin1())
        {
            obj = putCommand(splitData.at(1));
        }
        else
        {
            obj.insert(JsonKeys::error(), QLatin1String("Invalid command: " + splitData.at(0)));
        }
    }
    else
    {
        obj.insert(JsonKeys::error(), QLatin1String("Invalid format: " + data));
    }


   emit sendData(QJsonDocument(obj).toJson());
}
