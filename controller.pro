QT += core
QT -= gui

TARGET = controller
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

#DEFINES += WITH_NONAMESPACES

GSOAPDIR = ../../../../Code/gsoap-2.8/gsoap

INCLUDEPATH += $$GSOAPDIR/plugin \
                ./server

SOURCES += ./server/webserver.c \
            ./server/options.c \
            $$GSOAPDIR/plugin/httpget.c \
            $$GSOAPDIR/plugin/httppost.c \
            $$GSOAPDIR/plugin/httpform.c \
            $$GSOAPDIR/plugin/logging.c \
            $$GSOAPDIR/stdsoap2.c \
            ./server/soapC.c

SOURCES += main.cpp

