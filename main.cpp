#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QCommandLineParser>

#include "fullcommandhandler.h"
#include "hardwarecontroller.h"
#include "panelboard.h"
#include "interlockhandling.h"

#include "commandline.h"
#include "testcommandhandler.h"
#include "fullcommandhandler.h"

#include "clientsocket.h"


//const char* handlePost(int isPost, const char* url, const char* data, int len, int* respLen)
//{
//    static QByteArray respData;

//    if (g_Handler)
//    {
//        respData = g_Handler->putCommand(QByteArray(url), QByteArray(data, len));
//    }

//    *respLen = respData.length();
//    return respData.data();
//}

//const char* handleGet(const char* url, const char* , int , int* respLen)
//{
//    static QByteArray respData;

//    if (g_Handler)
//    {
//        respData = g_Handler->getCommand(QByteArray(url));
//    }

//    *respLen = respData.length();
//    return respData.data();
//}


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

    QCommandLineOption testServerOption("testServer", QCoreApplication::translate("main", "Run test mode"));
    parser.addOption(testServerOption);


    parser.process(app);

    if (parser.isSet(testOption))
    {
        qDebug() << "Test";
        CommandLine c;
        c.run();
    }
    else
    {
        HardwareController hardwareControl;

        CommandHandler* pCmdHandler;
        PanelBoard *pPanelBoard;
        InterlockHandling *pInterlock;

        ClientSocket* pCmdSocket = new ClientSocket(&hardwareControl);

        if (parser.isSet(testServerOption))
        {
            qDebug() << "Test Server";
            pCmdHandler = new TestCommandHandler();
        }
        else
        {
            pPanelBoard = new PanelBoard(&hardwareControl);
            pInterlock = new InterlockHandling(&hardwareControl);

            pCmdHandler = new FullCommandHandler(&hardwareControl, pPanelBoard, pInterlock);

            dynamic_cast<FullCommandHandler*>(pCmdHandler)->test();
        }

        QObject::connect(pCmdSocket, SIGNAL(dataReceived(QByteArray)), pCmdHandler, SLOT(receiveData(QByteArray)));
        QObject::connect(pCmdHandler, SIGNAL(sendData(QByteArray)), pCmdSocket, SLOT(sendData(QByteArray)));

        app.exec();
    }

    return status;
}

