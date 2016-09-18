#include "interlockhandling.h"
#include "basepointcontroller.h"
#include "speedcontroller.h"

#include <QSet>
#include <QDebug>

enum BITMASKS {
    OUTERLOOP       = 0x1,
    INNERLOOP       = 0x2,
    STATIONOUTER    = 0x4,
    STATIONINNER    = 0x8,
    ENTRANCE        = 0x10,
    STATION         = 0x20,
    MAIN            = 0x40
};
InterlockHandling::InterlockHandling(HardwareController *pControl) :
    m_pController(pControl)
{
    updateEnabled();
}

void InterlockHandling::togglePoint(const QByteArray &pointName)
{
    BasePointController* pPoint = m_pController->getPoint(pointName);

    if (pPoint->enabled())
    {
        pPoint->toggle();
        updateEnabled();
    }
}


void InterlockHandling::setSpeed(const QByteArray &controller, int newSpeed)
{
    SpeedController* pCtrl = m_pController->getController(controller);
    if (pCtrl->enabled())
    {
        qDebug() << "Setting speed to " << newSpeed;
        pCtrl->setSpeed(newSpeed);
        updateEnabled();
    }
}

bool InterlockHandling::isValidMask(quint8 mask) const
{
    static QSet<quint8> invalidMasks;
    if (invalidMasks.isEmpty())
    {
        invalidMasks.insert(44);
        invalidMasks.insert(45);
        invalidMasks.insert(46);
        invalidMasks.insert(47);

        invalidMasks.insert(22);
        invalidMasks.insert(23);
        invalidMasks.insert(30);
        invalidMasks.insert(31);

        invalidMasks.insert(60);
        invalidMasks.insert(58);
        invalidMasks.insert(54);
        invalidMasks.insert(61);
        invalidMasks.insert(62);
        invalidMasks.insert(63);
        invalidMasks.insert(55);
        invalidMasks.insert(59);

        invalidMasks.insert(67);
        invalidMasks.insert(75);
        invalidMasks.insert(71);
        invalidMasks.insert(79);

        invalidMasks.insert(108);
        invalidMasks.insert(110);
        invalidMasks.insert(109);
        invalidMasks.insert(99);
        invalidMasks.insert(107);
        invalidMasks.insert(103);
        invalidMasks.insert(111);

        invalidMasks.insert(86);
        invalidMasks.insert(94);
        invalidMasks.insert(85);
        invalidMasks.insert(93);
        invalidMasks.insert(83);
        invalidMasks.insert(91);
        invalidMasks.insert(87);
        invalidMasks.insert(95);

        invalidMasks.insert(124);
        invalidMasks.insert(122);
        invalidMasks.insert(118);
        invalidMasks.insert(126);
        invalidMasks.insert(121);
        invalidMasks.insert(117);
        invalidMasks.insert(125);
        invalidMasks.insert(115);
        invalidMasks.insert(123);
        invalidMasks.insert(119);
        invalidMasks.insert(127);
    }

    return !invalidMasks.contains(mask);
}

void InterlockHandling::updateEnabled()
{
    quint8 mask = 0x0;

    if (m_pController->getController("outerloop")->speed()!=0)   mask |= OUTERLOOP;
    if (m_pController->getController("innerloop")->speed()!=0)   mask |= INNERLOOP;
    if (m_pController->getController("stationouter")->speed()!=0)   mask |= STATIONOUTER;
    if (m_pController->getController("stationinner")->speed()!=0)   mask |= STATIONINNER;

    if (m_pController->getPoint("stationentrancecrossover")->direction()==BasePointController::ePointRight) mask |= ENTRANCE;
    if (m_pController->getPoint("upstationcrossover")->direction()==BasePointController::ePointLeft ||
            m_pController->getPoint("downstationcrossover")->direction()==BasePointController::ePointRight)
    {
        mask |= STATION;
    }
    if (m_pController->getPoint("upmaincrossover")->direction()==BasePointController::ePointLeft
            || m_pController->getPoint("downmaincrossover")->direction()==BasePointController::ePointRight)
    {
        mask |= MAIN;
    }

    Q_ASSERT_X(isValidMask(mask), "InterLock", "Invalid mask set");

    m_pController->getController("outerloop")->setEnabled(isValidMask(mask | OUTERLOOP));
    m_pController->getController("innerloop")->setEnabled(isValidMask(mask | INNERLOOP));
    m_pController->getController("stationouter")->setEnabled(isValidMask(mask | STATIONOUTER));
    m_pController->getController("stationinner")->setEnabled(isValidMask(mask | STATIONINNER));

    m_pController->getPoint("stationentrancecrossover")->setEnabled(isValidMask(mask | ENTRANCE));
    m_pController->getPoint("upstationcrossover")->setEnabled(isValidMask(mask | STATION));
    m_pController->getPoint("downstationcrossover")->setEnabled(isValidMask(mask | STATION));
    m_pController->getPoint("upmaincrossover")->setEnabled(isValidMask(mask | MAIN));
    m_pController->getPoint("downmaincrossover")->setEnabled(isValidMask(mask | MAIN));
}


