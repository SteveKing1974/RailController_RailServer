QT += core network
QT -= gui

TARGET = controller
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += CONTROLLER QT_RESTRICTED_CAST_FROM_ASCII

INCLUDEPATH += \
                ./server \
                ./controller \
                ../Common

SOURCES += \
    ../Common/clientsocket.cpp \
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
    testcommands.cpp \
    controller/isolatorcontroller.cpp

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
    testcommands.h \
    controller/isolatorcontroller.h \
    ../Common/clientsocket.h

SOURCES += main.cpp

linux-rasp-pi-g++: {
    target.path = /home/pi/Rail
    INSTALLS += target

    html.files= ./resources/controllers.html \
                ./resources/panel.html \
                ./resources/test.html
    html.path=/home/pi/Rail


    png.files= ./resources/png/blueindicator.png \
                ./resources/png/downMainCrossOverLever_off.png \
                ./resources/png/downMainCrossOverLever_on.png \
                ./resources/png/downSiding1Lever_off.png \
                ./resources/png/downSiding1Lever_on.png \
                ./resources/png/downSiding2Lever_off.png \
                ./resources/png/downSiding2Lever_on.png \
                ./resources/png/downSidingLowerLever_off.png \
                ./resources/png/downSidingLowerLever_on.png \
                ./resources/png/downSidingUpperLever_off.png \
                ./resources/png/downSidingUpperLever_on.png \
                ./resources/png/downStationCrossOverLever_off.png \
                ./resources/png/downStationCrossOverLever_on.png \
                ./resources/png/greenindicator.png \
                ./resources/png/greyindicator.png \
                ./resources/png/panel.png \
                ./resources/png/redindicator.png \
                ./resources/png/stationEntranceLever_off.png \
                ./resources/png/stationEntranceLever_on.png \
                ./resources/png/stationSidingLever_off.png \
                ./resources/png/stationSidingLever_on.png \
                ./resources/png/upMainCrossOverLever_off.png \
                ./resources/png/upMainCrossOverLever_on.png \
                ./resources/png/upSiding1Lever_off.png \
                ./resources/png/upSiding1Lever_on.png \
                ./resources/png/upSiding2Lever_off.png \
                ./resources/png/upSiding2Lever_on.png \
                ./resources/png/upSidingLever_off.png \
                ./resources/png/upSidingLever_on.png \
                ./resources/png/upStationCrossOverLever_off.png \
                ./resources/png/upStationCrossOverLever_on.png \
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
