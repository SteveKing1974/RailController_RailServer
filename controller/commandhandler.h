#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QByteArray>

#include <QJsonObject>
#include <QObject>

class CommandHandler : public QObject
{
    Q_OBJECT

public:
    virtual ~CommandHandler() {}

    virtual QJsonObject handleCommand(const QJsonObject& data) = 0;

public slots:
    void receiveData(const QByteArray& data);

signals:
    void sendData(const QByteArray& data);
};

#endif // COMMANDHANDLER_H
