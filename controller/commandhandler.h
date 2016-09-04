#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QByteArray>

#include <QJsonDocument>

class CommandHandler
{
public:
    virtual ~CommandHandler() {}

    virtual QByteArray getCommand(const QByteArray& url) const = 0;
    virtual QByteArray putCommand(const QByteArray& url, const QByteArray& data) const = 0;

protected:
    static QJsonDocument fromPUTData(const QByteArray& data);
};

#endif // COMMANDHANDLER_H
