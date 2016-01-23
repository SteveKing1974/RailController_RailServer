#include <QCoreApplication>
#include <QDebug>
#include <QString>

extern "C" {
#include "webserver.h"
}

QString g_String;

const char* handlePost(const char* data, int len, int* respLen)
{
    qDebug() << data;

    g_String = "{\"data\" : \"2\"}";

    *respLen = g_String.length();
    return g_String.toLatin1().data();
}

int main(int argc, char *argv[])
{
    int i = serverMain(argc, argv, handlePost);
    return i;
}

