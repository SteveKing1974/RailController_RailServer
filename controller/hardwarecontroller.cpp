#include "hardwarecontroller.h"
#include "wiringPi.h"
#include "mcp23s17.h"
#include "softPwm.h"

const int k_PortsPerExtender = 16;
enum {
    CONTROLLER1_IN1 = 5,
    CONTROLLER1_IN2 = 6,
    CONTROLLER1_PWM = 13,

    CONTROLLER2_IN1 = 19,
    CONTROLLER2_IN2 = 26,
    CONTROLLER2_PWM = 12,

    CONTROLLER3_IN1 = 16,
    CONTROLLER3_IN2 = 20,
    CONTROLLER3_PWM = 21,

    CONTROLLER4_IN1 = 18,
    CONTROLLER4_IN2 = 23,
    CONTROLLER4_PWM = 24,

    CONTROLLER1_2_STDBY = 23,
    CONTROLLER3_4_STDBY = 24,

    EXTENDERA       = 128,
    RELAY_1         = EXTENDERA,
    RELAY_2,
    RELAY_3,
    RELAY_4,
    RELAY_5,
    RELAY_6,
    RELAY_7,
    RELAY_8,
    RELAY_9,
    RELAY_10,
    RELAY_11,
    RELAY_12,
    RELAY_13,
    RELAY_14,
    RELAY_15,
    RELAY_16,

    EXTENDERB       = EXTENDERA + k_PortsPerExtender,
    RELAY_17        = EXTENDERB,
    RELAY_18,
    RELAY_19,
    RELAY_20,
    RELAY_21,
    RELAY_22,
    RELAY_23,
    RELAY_24,
    RELAY_25,
    RELAY_26,
    RELAY_27,
    RELAY_28,
    RELAY_29,
    RELAY_30,
    RELAY_31,
    RELAY_32,

    EXTENDERC       = EXTENDERB + k_PortsPerExtender,
    RELAY_33        = EXTENDERC,
    RELAY_34,
    RELAY_35,
    RELAY_36,
    RELAY_37,
    RELAY_38,
    RELAY_39,
    RELAY_40
};
HardwareController::HardwareController(QObject *parent) : QObject(parent)
{
    wiringPiSetup () ;
    mcp23s17Setup(EXTENDERA, 0, 0);
    mcp23s17Setup(EXTENDERB, 0, 1);
    mcp23s17Setup(EXTENDERC, 0, 2);

    // Put controllers into standby until setup is done
    pinMode(CONTROLLER1_2_STDBY, OUTPUT);
    digitalWrite(CONTROLLER1_2_STDBY, LOW);
    pinMode(CONTROLLER3_4_STDBY, OUTPUT);
    digitalWrite(CONTROLLER3_4_STDBY, LOW);

    m_Controllers.insert("outerLoop", new SpeedController(CONTROLLER1_IN1, CONTROLLER1_IN2, CONTROLLER1_PWM, 1));
    m_Controllers.insert("innerLoop", new SpeedController(CONTROLLER2_IN1, CONTROLLER2_IN2, CONTROLLER2_PWM, 2));
    m_Controllers.insert("stationOuter", new SpeedController(CONTROLLER3_IN1, CONTROLLER3_IN2, CONTROLLER3_PWM, 3));
    m_Controllers.insert("stationInner", new SpeedController(CONTROLLER4_IN1, CONTROLLER4_IN2, CONTROLLER4_PWM, 4));


    m_Points.insert("innerStationSwitch", new PointController(RELAY_1, RELAY_2));
    m_Points.insert("innerSwitchLeft", new PointController(RELAY_3, RELAY_4));
    m_Points.insert("innerSwitchRight", new PointController(RELAY_5, RELAY_6));
    m_Points.insert("leftSidingSwitch", new PointController(RELAY_7, RELAY_8));
    m_Points.insert("leftSidingSwitch2", new PointController(RELAY_9, RELAY_10));
    m_Points.insert("outerSwitchLeft", new PointController(RELAY_11, RELAY_12));
    m_Points.insert("outerSwitchRight", new PointController(RELAY_13, RELAY_14));
    m_Points.insert("rightSidingSwitch2", new PointController(RELAY_15, RELAY_16));

    m_Points.insert("stationInnerLoopSwitchLeft", new PointController(RELAY_17, RELAY_18));
    m_Points.insert("stationInnerLoopSwitchRight", new PointController(RELAY_19, RELAY_20));
    m_Points.insert("stationOuterEntrance", new PointController(RELAY_21, RELAY_22));
    m_Points.insert("stationOuterLoopSwitchLeft", new PointController(RELAY_23, RELAY_24));
    m_Points.insert("stationOuterRightSiding1", new PointController(RELAY_25, RELAY_26));
    m_Points.insert("stationOuterLoopSwitchRight", new PointController(RELAY_27, RELAY_28));

    // Controllers can come out of standby now
    digitalWrite(CONTROLLER1_2_STDBY, HIGH);
    digitalWrite(CONTROLLER3_4_STDBY, HIGH);
}

HardwareController::~HardwareController()
{
    qDeleteAll(m_Points);
    qDeleteAll(m_Controllers);
}

QList<QByteArray> HardwareController::allPoints() const
{
    return m_Points.keys();
}

QList<QByteArray> HardwareController::allControllers() const
{
    return m_Controllers.keys();
}

PointController *HardwareController::getPoint(const QByteArray &name) const
{
    if (m_Points.contains(name))
    {
        return m_Points.value(name);
    }

    return 0;
}

SpeedController *HardwareController::getController(const QByteArray &name) const
{
    if (m_Controllers.contains(name))
    {
        return m_Controllers.value(name);
    }

    return 0;
}

