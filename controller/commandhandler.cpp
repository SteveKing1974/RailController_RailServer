#include "commandhandler.h"


QJsonDocument CommandHandler::fromPUTData(const QByteArray &data)
{
    QByteArray copyOfCommand = data;
    copyOfCommand.replace("=", "\": \"");
    copyOfCommand.replace("&", "\" , \"");
    copyOfCommand.push_front("{ \"");
    copyOfCommand.push_back("\" }");

    return QJsonDocument::fromJson(copyOfCommand);
}
