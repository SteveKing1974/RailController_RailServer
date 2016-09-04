QT += core
QT -= gui

TARGET = controller
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

#DEFINES += WITH_NONAMESPACES

GSOAPDIR = ../../gsoap-2.8/gsoap

INCLUDEPATH += $$GSOAPDIR/plugin \
                ./server \
                ./controller \
                /usr/local/include

SOURCES += ./server/webserver.c \
            ./server/options.c \
            $$GSOAPDIR/plugin/httpget.c \
            $$GSOAPDIR/plugin/httppost.c \
            $$GSOAPDIR/plugin/httpform.c \
            $$GSOAPDIR/plugin/logging.c \
            $$GSOAPDIR/stdsoap2.c \
            ./server/soapC.c \
    controller/speedcontroller.cpp \
    controller/layoutnode.cpp \
    controller/switchcontroller.cpp \
    controller/panelboard.cpp \
    controller/basepointcontroller.cpp \
    controller/pointgroup.cpp \
    controller/interlockhandling.cpp \
    commandline.cpp \
    controller/testcommandhandler.cpp \
    controller/fullcommandhandler.cpp \
    controller/commandhandler.cpp \
    testcommands.cpp

SOURCES +=  ./controller/hardwarecontroller.cpp \
            ./controller/pointcontroller.cpp

HEADERS +=  ./controller/hardwarecontroller.h \
            ./controller/pointcontroller.h \
    controller/speedcontroller.h \
    controller/commandhandler.h \
    controller/layoutnode.h \
    controller/switchcontroller.h \
    controller/panelboard.h \
    dummyWiringPi/softPwm.h \
    controller/basepointcontroller.h \
    controller/pointgroup.h \
    controller/interlockhandling.h \
    commandline.h \
    controller/testcommandhandler.h \
    controller/fullcommandhandler.h \
    testcommands.h

SOURCES += main.cpp

*pi*: {
    target.path = /home/pi/Rail
    INSTALLS += target

    html.files= ./resources/controllers.html \
                ./resources/panel.html \
                ./resources/test.html
    html.path=/home/pi/Rail


    png.files= ./resources/png/blueindicator.png \
                ./resources/png/downmaincrossover_off.png \
                ./resources/png/downmaincrossover_on.png \
                ./resources/png/downsiding1_off.png \
                ./resources/png/downsiding1_on.png \
                ./resources/png/downsiding2_off.png \
                ./resources/png/downsiding2_on.png \
                ./resources/png/downstationcrossover_off.png \
                ./resources/png/downstationcrossover_on.png \
                ./resources/png/greenindicator.png \
                ./resources/png/greyindicator.png \
                ./resources/png/panel.png \
                ./resources/png/redindicator.png \
                ./resources/png/stationentrancecrossover_off.png \
                ./resources/png/stationentrancecrossover_on.png \
                ./resources/png/upmaincrossover_off.png \
                ./resources/png/upmaincrossover_on.png \
                ./resources/png/upsiding1_off.png \
                ./resources/png/upsiding1_on.png \
                ./resources/png/upsiding2_off.png \
                ./resources/png/upsiding2_on.png \
                ./resources/png/upstationcrossover_off.png \
                ./resources/png/upstationcrossover_on.png \
                ./resources/png/yellowindicator.png

    png.path=/home/pi/Rail/png

    INSTALLS+=html png

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
