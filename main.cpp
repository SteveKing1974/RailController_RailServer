#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QCommandLineParser>

#include "commandhandler.h"
#include "hardwarecontroller.h"
#include "panelboard.h"
#include "interlockhandling.h"

#include "commandline.h"

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
    int status = 0;

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption testOption("test", QCoreApplication::translate("main", "Run test mode"));
    parser.addOption(testOption);


    parser.process(app);

    HardwareController hardwareControl;

    if (parser.isSet(testOption))
    {
        CommandLine c;
        c.run();
    }
    else
    {
        PanelBoard panelBoard(&hardwareControl);
        InterlockHandling interlock(&hardwareControl);

        g_Handler = new CommandHandler(&hardwareControl, &panelBoard, &interlock);

        status = serverMain(argc, argv, handlePost, handleGet);

        delete g_Handler;
    }

    return status;
}

