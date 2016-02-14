#include "hardwarecontroller.h"
#include "wiringPi.h"
#include "mcp23s17.h"
#include "softPwm.h"
#include "pointgroup.h"
#include "pointcontroller.h"

const int k_PortsPerExtender = 16;
enum {
    CONTROLLER1_IN1 = 21,
    CONTROLLER1_IN2 = 22,
    CONTROLLER1_PWM = 23,

    CONTROLLER2_IN1 = 24,
    CONTROLLER2_IN2 = 25,
    CONTROLLER2_PWM = 26,

    CONTROLLER3_IN1 = 27,
    CONTROLLER3_IN2 = 28,
    CONTROLLER3_PWM = 29,

    CONTROLLER4_IN1 = 1,
    CONTROLLER4_IN2 = 4,
    CONTROLLER4_PWM = 5,

    CONTROLLER1_2_STDBY = 2,
    CONTROLLER3_4_STDBY = 3,

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
    //mcp23s17Setup(EXTENDERA, 0, 0);
    //mcp23s17Setup(EXTENDERB, 0, 1);
    //mcp23s17Setup(EXTENDERC, 0, 2);

    // Put controllers into standby until setup is done
    pinMode(CONTROLLER1_2_STDBY, OUTPUT);
    digitalWrite(CONTROLLER1_2_STDBY, LOW);
    pinMode(CONTROLLER3_4_STDBY, OUTPUT);
    digitalWrite(CONTROLLER3_4_STDBY, LOW);

    m_Controllers.insert("outerloop", new SpeedController(CONTROLLER1_IN1, CONTROLLER1_IN2, CONTROLLER1_PWM, 1));
    m_Controllers.insert("innerloop", new SpeedController(CONTROLLER2_IN1, CONTROLLER2_IN2, CONTROLLER2_PWM, 2));
    m_Controllers.insert("stationouter", new SpeedController(CONTROLLER3_IN1, CONTROLLER3_IN2, CONTROLLER3_PWM, 3));
    m_Controllers.insert("stationinner", new SpeedController(CONTROLLER4_IN1, CONTROLLER4_IN2, CONTROLLER4_PWM, 4));


    PointController* pA = new PointController(RELAY_1, RELAY_2);
    BasePointController* pB = new BasePointController();
    m_Points.insert("stationentrancecrossovera", pA);
    m_Points.insert("stationentrancecrossoverb", pB);
    m_Points.insert("stationentrancecrossover", new PointGroup(pA, pB));

    pA = new PointController(RELAY_11, RELAY_12, PointController::ePointRight);
    pB = new BasePointController(PointController::ePointRight);
    m_Points.insert("upmaincrossovera", pA);
    m_Points.insert("upmaincrossoverb", pB);
    m_Points.insert("upmaincrossover", new PointGroup(pA, pB));

    pA = new PointController(RELAY_13, RELAY_14);
    pB = new BasePointController();
    m_Points.insert("downmaincrossovera", pA);
    m_Points.insert("downmaincrossoverb", pB);
    m_Points.insert("downmaincrossover", new PointGroup(pA, pB));

    pA = new PointController(RELAY_23, RELAY_24, PointController::ePointRight);
    pB = new BasePointController(PointController::ePointRight);
    m_Points.insert("upstationcrossovera", pA);
    m_Points.insert("upstationcrossoverb", pB);
    m_Points.insert("upstationcrossover", new PointGroup(pA, pB));

    pA = new PointController(RELAY_27, RELAY_28);
    pB = new BasePointController();
    m_Points.insert("downstationcrossovera", pA);
    m_Points.insert("downstationcrossoverb", pB);
    m_Points.insert("downstationcrossover", new PointGroup(pA, pB));


    m_Points.insert("upsiding1", new PointController(RELAY_7, RELAY_8));
    m_Points.insert("upsiding2", new PointController(RELAY_9, RELAY_10));

    m_Points.insert("downsiding1", new PointController(RELAY_25, RELAY_26));
    m_Points.insert("downsiding2", new PointController(RELAY_15, RELAY_16));


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

BasePointController *HardwareController::getPoint(const QByteArray &name) const
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

