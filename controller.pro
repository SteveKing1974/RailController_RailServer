QT += core
QT -= gui

TARGET = controller
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

#DEFINES += WITH_NONAMESPACES

GSOAPDIR = ../../../../Code/gsoap-2.8/gsoap

INCLUDEPATH += $$GSOAPDIR/plugin \
                ./server \
                ./controller

SOURCES += ./server/webserver.c \
            ./server/options.c \
            $$GSOAPDIR/plugin/httpget.c \
            $$GSOAPDIR/plugin/httppost.c \
            $$GSOAPDIR/plugin/httpform.c \
            $$GSOAPDIR/plugin/logging.c \
            $$GSOAPDIR/stdsoap2.c \
            ./server/soapC.c \
    controller/speedcontroller.cpp \
    controller/commandhandler.cpp

SOURCES +=  ./controller/hardwarecontroller.cpp \
            ./controller/pointcontroller.cpp

HEADERS +=  ./controller/hardwarecontroller.h \
            ./controller/pointcontroller.h \
    controller/speedcontroller.h \
    controller/commandhandler.h

SOURCES += main.cpp

*pi*: {
    target.path = /home/pi/Rail
    INSTALLS += target

    INCLUDEPATH += ./wiringPi/wiringPi/

    SOURCES +=  \
        ./wiringPi/wiringPi/mcp23s17.c \
        ./wiringPi/wiringPi/wiringPiSPI.c \
        ./wiringPi/wiringPi/wiringPi.c \
        ./wiringPi/wiringPi/softPwm.c \
        ./wiringPi/wiringPi/softTone.c \
        ./wiringPi/wiringPi/piHiPri.c

    HEADERS += \
        ./wiringPi/wiringPi/mcp23s17.h \
        ./wiringPi/wiringPi/wiringPiSPI.h \
        ./wiringPi/wiringPi/wiringPi.h \
        ./wiringPi/wiringPi/softPwm.h \
        ./wiringPi/wiringPi/softTone.h
} else {
    INCLUDEPATH += ./dummyWiringPi/

    SOURCES +=  \
        ./dummyWiringPi/mcp23s17.cpp \
        ./dummyWiringPi/wiringPi.cpp

    HEADERS += \
        ./dummyWiringPi/mcp23s17.h \
        ./dummyWiringPi/wiringPi.h
}
