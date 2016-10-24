#include "hardwarecontroller.h"
#include "wiringPi.h"
#include "mcp23s17.h"
#include "softPwm.h"
#include "pointgroup.h"
#include "pointcontroller.h"

#include <QDebug>

const int k_PortsPerExtender = 16;
enum {
    CONTROLLER1_IN1 = 2,
    CONTROLLER1_IN2 = 3,
    CONTROLLER1_PWM = 4,

    CONTROLLER2_IN1 = 21,
    CONTROLLER2_IN2 = 22,
    CONTROLLER2_PWM = 26,

    CONTROLLER3_IN1 = 23,
    CONTROLLER3_IN2 = 24,
    CONTROLLER3_PWM = 27,

    CONTROLLER4_IN1 = 25,
    CONTROLLER4_IN2 = 28,
    CONTROLLER4_PWM = 29,

    CONTROLLER1_2_STDBY = 0,
    CONTROLLER3_4_STDBY = 1,

    EXTENDERA       = 128,
    ISOLATE_STATION_ENTRANCE_1         = EXTENDERA,
    ISOLATE_STATION_ENTRANCE_2,
    ISOLATE_UP_STATION_CROSSOVER_1,
    ISOLATE_UP_STATION_CROSSOVER_2,
    ISOLATE_UP_MAIN_CROSSOVER_1,
    ISOLATE_UP_MAIN_CROSSOVER_2,
    ISOLATE_DOWN_STATION_CROSSOVER_1,
    ISOLATE_DOWN_STATION_CROSSOVER_2,
    ISOLATE_DOWN_MAIN_CROSSOVER_1,
    ISOLATE_DOWN_MAIN_CROSSOVER_2,
    ISOLATE_TOP_SIDING_DOWN,
    ISOLATE_BOTTOM_SIDING_DOWN,
    ISOLATE_STATION_SIDING_DOWN,
    ISOLATE_TOP_SIDING_UP,

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
    ISOLATE_CONTROLLER_2_1        = EXTENDERC,
    ISOLATE_CONTROLLER_2_2,
    ISOLATE_CONTROLLER_1_1,
    ISOLATE_CONTROLLER_1_2,
    ISOLATE_CONTROLLER_3_1,
    ISOLATE_CONTROLLER_3_2,
    ISOLATE_CONTROLLER_4_1,
    ISOLATE_CONTROLLER_4_2
};

HardwareController::HardwareController(QObject *parent) : QObject(parent)
{
    wiringPiSetup () ;
    mcp23s17Setup(EXTENDERA, 0, 0);
    mcp23s17Setup(EXTENDERB, 0, 1);
    mcp23s17Setup(EXTENDERC, 0, 2);

    // Set everything to an output. Write high before the
    // setting to output so it doesn't toggle the power on
    for (int i=0; i<k_PortsPerExtender; ++i)
    {
        setLine(EXTENDERA + i, HIGH);
        pinMode (EXTENDERA + i, OUTPUT);
    }
    for (int i=0; i<k_PortsPerExtender; ++i)
    {
        setLine(EXTENDERB + i, HIGH);
        pinMode (EXTENDERB + i, OUTPUT);
    }
    for (int i=0; i<k_PortsPerExtender; ++i)
    {
        setLine(EXTENDERC + i, HIGH);
        pinMode (EXTENDERC + i, OUTPUT);
    }

    pinMode(CONTROLLER1_IN1, OUTPUT);
    pinMode(CONTROLLER1_IN2, OUTPUT);
    pinMode(CONTROLLER1_PWM, OUTPUT);
    pinMode(CONTROLLER2_IN1, OUTPUT);
    pinMode(CONTROLLER2_IN2, OUTPUT);
    pinMode(CONTROLLER2_PWM, OUTPUT);
    pinMode(CONTROLLER3_IN1, OUTPUT);
    pinMode(CONTROLLER3_IN2, OUTPUT);
    pinMode(CONTROLLER3_PWM, OUTPUT);
    pinMode(CONTROLLER4_IN1, OUTPUT);
    pinMode(CONTROLLER4_IN2, OUTPUT);
    pinMode(CONTROLLER4_PWM, OUTPUT);
    pinMode(CONTROLLER1_2_STDBY, OUTPUT);
    pinMode(CONTROLLER3_4_STDBY, OUTPUT);


    // Put controllers into standby until setup is done
    setLine(CONTROLLER1_2_STDBY, LOW);
    setLine(CONTROLLER3_4_STDBY, LOW);

    m_Controllers.insert("innerloop", new SpeedController(CONTROLLER1_IN1, CONTROLLER1_IN2, CONTROLLER1_PWM, 1, ISOLATE_CONTROLLER_1_1, ISOLATE_CONTROLLER_1_2));
    m_Controllers.insert("outerloop", new SpeedController(CONTROLLER2_IN1, CONTROLLER2_IN2, CONTROLLER2_PWM, 2, ISOLATE_CONTROLLER_2_1, ISOLATE_CONTROLLER_2_2));
    m_Controllers.insert("stationinner", new SpeedController(CONTROLLER3_IN1, CONTROLLER3_IN2, CONTROLLER3_PWM, 3, ISOLATE_CONTROLLER_3_1, ISOLATE_CONTROLLER_3_2));
    m_Controllers.insert("stationouter", new SpeedController(CONTROLLER4_IN1, CONTROLLER4_IN2, CONTROLLER4_PWM, 4, ISOLATE_CONTROLLER_4_1, ISOLATE_CONTROLLER_4_2));

    // Add isolators
    m_Isolators.insert("topsidingdown", new IsolatorController(ISOLATE_TOP_SIDING_DOWN));
    m_Isolators.insert("bottomsidingdown", new IsolatorController(ISOLATE_BOTTOM_SIDING_DOWN));
    m_Isolators.insert("stationsidingdown", new IsolatorController(ISOLATE_STATION_SIDING_DOWN));
    m_Isolators.insert("topsidingup", new IsolatorController(ISOLATE_TOP_SIDING_UP));


    // Points
    PointController* pA = new PointController(RELAY_15, RELAY_16);
    BasePointController* pB = new BasePointController();
    m_Points.insert("stationentrancecrossovera", pA);
    m_Points.insert("stationentrancecrossoverb", pB);
    m_Points.insert("stationentrancecrossover", new PointGroup(pA, pB, ISOLATE_STATION_ENTRANCE_1, ISOLATE_STATION_ENTRANCE_2, PointController::ePointRight));

    pA = new PointController(RELAY_18, RELAY_17, PointController::ePointRight);
    pB = new BasePointController(PointController::ePointRight);
    m_Points.insert("upmaincrossovera", pA);
    m_Points.insert("upmaincrossoverb", pB);
    m_Points.insert("upmaincrossover", new PointGroup(pA, pB, ISOLATE_UP_MAIN_CROSSOVER_1, ISOLATE_UP_MAIN_CROSSOVER_2, PointController::ePointLeft));

    pA = new PointController(RELAY_20, RELAY_19);
    pB = new BasePointController();
    m_Points.insert("downmaincrossovera", pA);
    m_Points.insert("downmaincrossoverb", pB);
    m_Points.insert("downmaincrossover", new PointGroup(pA, pB, ISOLATE_DOWN_MAIN_CROSSOVER_1, ISOLATE_DOWN_MAIN_CROSSOVER_2, PointController::ePointRight));

    pA = new PointController(RELAY_22, RELAY_21, PointController::ePointRight);
    pB = new BasePointController(PointController::ePointRight);
    m_Points.insert("upstationcrossovera", pA);
    m_Points.insert("upstationcrossoverb", pB);
    m_Points.insert("upstationcrossover", new PointGroup(pA, pB, ISOLATE_UP_STATION_CROSSOVER_1, ISOLATE_UP_STATION_CROSSOVER_2, PointController::ePointLeft));

    pA = new PointController(RELAY_24, RELAY_23);
    pB = new BasePointController();
    m_Points.insert("downstationcrossovera", pA);
    m_Points.insert("downstationcrossoverb", pB);
    m_Points.insert("downstationcrossover", new PointGroup(pA, pB, ISOLATE_DOWN_STATION_CROSSOVER_1, ISOLATE_DOWN_STATION_CROSSOVER_2, PointController::ePointRight));


    m_Points.insert("upsiding1", new PointController(RELAY_25, RELAY_26));
    m_Points.insert("upsiding2", new PointController(RELAY_27, RELAY_28));

    m_Points.insert("downsiding1", new PointController(RELAY_29, RELAY_30));
    m_Points.insert("downsiding2", new PointController(RELAY_31, RELAY_32));


    // Controllers can come out of standby now
    setLine(CONTROLLER1_2_STDBY, HIGH);
    setLine(CONTROLLER3_4_STDBY, HIGH);
}

HardwareController::~HardwareController()
{
    qDeleteAll(m_Points);
    qDeleteAll(m_Controllers);
    qDeleteAll(m_Isolators);
}

QList<QByteArray> HardwareController::allPoints() const
{
    return m_Points.keys();
}

QList<QByteArray> HardwareController::allControllers() const
{
    return m_Controllers.keys();
}

QList<QByteArray> HardwareController::allIsolators() const
{
    return m_Isolators.keys();
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

IsolatorController *HardwareController::getIsolator(const QByteArray &name) const
{
    if (m_Isolators.contains(name))
    {
        return m_Isolators.value(name);
    }

    return 0;
}

void HardwareController::setLine(int lineID, int value)
{
    qDebug() << "Setting line " << lineID << " to " << value;
    digitalWrite(lineID, value);
}

