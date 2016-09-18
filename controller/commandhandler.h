#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QByteArray>

#include <QJsonObject>

class CommandHandler
{
public:
    virtual ~CommandHandler() {}

    virtual QByteArray getCommand(const QByteArray& url) const = 0;
    virtual QByteArray putCommand(const QByteArray& url, const QByteArray& data) const = 0;

protected:
    static QJsonObject fromPUTData(const QByteArray& data);
};

#endif // COMMANDHANDLER_H
