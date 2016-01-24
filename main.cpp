#include <QCoreApplication>
#include <QDebug>
#include <QString>

#include "commandhandler.h"
#include "hardwarecontroller.h"

extern "C" {
#include "webserver.h"
}

static CommandHandler* g_Handler = 0;

const char* handlePost(int isPost, const char* url, const char* data, int len, int* respLen)
{
    static QByteArray respData;

    if (g_Handler)
    {
        respData = g_Handler->putCommand(QByteArray(url), QByteArray(data, len));
    }

    *respLen = respData.length();
    return respData.data();
}

const char* handleGet(const char* url, const char* , int , int* respLen)
{
    static QByteArray respData;

    if (g_Handler)
    {
        respData = g_Handler->getCommand(QByteArray(url));
    }

    *respLen = respData.length();
    return respData.data();
}


int main(int argc, char *argv[])
{
    HardwareController hardwareControl;
    g_Handler = new CommandHandler(&hardwareControl);

    int i = serverMain(argc, argv, handlePost, handleGet);

    delete g_Handler;

    return i;
}

