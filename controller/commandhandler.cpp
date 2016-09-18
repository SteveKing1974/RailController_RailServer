#include "commandhandler.h"

#include <QJsonDocument>

QJsonObject CommandHandler::fromPUTData(const QByteArray &data)
{
    QByteArray copyOfCommand = data;
    copyOfCommand.replace("=", "\": \"");
    copyOfCommand.replace("&", "\" , \"");
    copyOfCommand.push_front("{ \"");
    copyOfCommand.push_back("\" }");

    return QJsonDocument::fromJson(copyOfCommand).object();
}
