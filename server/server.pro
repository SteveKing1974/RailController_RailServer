QT += core
QT -= gui

TARGET = Sever
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += WITH_NONAMESPACES
# gcc -DWITH_COOKIES -DWITH_ZLIB  -lpthread -lz

GSOAPDIR = ../../../../Code/gsoap-2.8/gsoap

INCLUDEPATH += $$GSOAPDIR/plugin

SOURCES += webserver.c \
            options.c \
            $$GSOAPDIR/plugin/httpget.c \
            $$GSOAPDIR/plugin/httppost.c \
            $$GSOAPDIR/plugin/httpform.c \
            $$GSOAPDIR/plugin/logging.c \
            $$GSOAPDIR/stdsoap2.c \
            soapC.c



