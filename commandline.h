#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QObject>

class CommandLine : public QObject
{
    Q_OBJECT
public:
    explicit CommandLine(QObject *parent = 0);

    int run();
signals:

public slots:
};

#endif // COMMANDLINE_H
