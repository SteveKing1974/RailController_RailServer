#include <QCoreApplication>
#include <QDebug>
#include <QString>

#include "commandhandler.h"
#include "hardwarecontroller.h"

extern "C" {
#include "webserver.h"
}

static CommandHandler* g_Handler = 0;

const char* handlePost(const char* data, int len, int* respLen)
{
    static QByteArray respData;

    if (g_Handler)
    {
        respData = g_Handler->parseCommand(QByteArray(data, len));
    }

    *respLen = respData.length();
    return respData.data();
}

int main(int argc, char *argv[])
{
    HardwareController hardwareControl;
    g_Handler = new CommandHandler(&hardwareControl);

    int i = serverMain(argc, argv, handlePost);

    delete g_Handler;

    return i;
}

