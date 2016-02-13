#include "panelboard.h"

#include <QDebug>

PanelBoard::PanelBoard(const HardwareController *pCtrl)
{
    LayoutNode* dummyOuter = new LayoutNode();

    LayoutNode* outerRight = new LayoutNode();
    LayoutNode* outerLeft = new LayoutNode();
    LayoutNode* outerCenter = new LayoutNode();

    LayoutNode* outerToInnerLeft = new LayoutNode();
    LayoutNode* outerToInnerRight = new LayoutNode();

    LayoutNode* dummyInner = new LayoutNode();

    LayoutNode* innerBetweenPoints = new LayoutNode();
    LayoutNode* innerRight = new LayoutNode();
    LayoutNode* innerLeft = new LayoutNode();
    LayoutNode* innerCenter = new LayoutNode();

    LayoutNode* innerToStation = new LayoutNode();

    LayoutNode* dummyStationOuter = new LayoutNode();
    LayoutNode* stationOuterBetweenPoints = new LayoutNode();
    LayoutNode* stationOuterRight = new LayoutNode();
    LayoutNode* stationOuterLeft = new LayoutNode();
    LayoutNode* stationOuterCenter = new LayoutNode();

    LayoutNode* stationSidingRight1 = new LayoutNode();
    LayoutNode* dummyRightBetweenSidings = new LayoutNode();
    LayoutNode* stationSidingRight2 = new LayoutNode();
    LayoutNode* stationSidingRight3 = new LayoutNode();

    LayoutNode* stationOuterToInnerLeft = new LayoutNode();
    LayoutNode* stationOuterToInnerRight = new LayoutNode();

    LayoutNode* dummyStationInner = new LayoutNode();
    LayoutNode* stationInnerRight = new LayoutNode();
    LayoutNode* stationInnerCenter = new LayoutNode();

    LayoutNode* dummyLeftBetweenPoints = new LayoutNode();
    LayoutNode* stationSidingLeft1 = new LayoutNode();
    LayoutNode* dummyLeftBetweenSidings = new LayoutNode();
    LayoutNode* stationSidingLeft2 = new LayoutNode();
    LayoutNode* stationSidingLeft3 = new LayoutNode();


    dummyOuter->setNext(pCtrl->getPoint("downmaincrossovera"), outerRight, 0);
    dummyOuter->setPrev(outerCenter);

    outerRight->setPrev(pCtrl->getPoint("downmaincrossovera"), dummyOuter, outerToInnerRight);
    outerRight->setNext(outerLeft);

    outerLeft->setPrev(outerRight);
    outerLeft->setNext(pCtrl->getPoint("upmaincrossovera"), outerToInnerLeft, outerCenter);

    outerCenter->setPrev(pCtrl->getPoint("upmaincrossovera"), 0, outerLeft);
    outerCenter->setNext(dummyOuter);

    outerToInnerLeft->setPrev(pCtrl->getPoint("upmaincrossovera"), outerLeft, 0);
    outerToInnerLeft->setNext(pCtrl->getPoint("upmaincrossoverb"), innerCenter, 0);

    outerToInnerRight->setPrev(pCtrl->getPoint("downmaincrossovera"), 0, outerRight);
    outerToInnerRight->setNext(pCtrl->getPoint("downmaincrossoverb"), 0, innerBetweenPoints);

    //////

    dummyInner->setNext(pCtrl->getPoint("stationentrancecrossovera"), innerBetweenPoints, 0);
    dummyInner->setPrev(innerCenter);

    innerBetweenPoints->setPrev(pCtrl->getPoint("stationentrancecrossovera"), dummyInner, innerToStation);
    innerBetweenPoints->setNext(pCtrl->getPoint("downmaincrossoverb"), innerRight, outerToInnerRight);

    innerRight->setPrev(pCtrl->getPoint("downmaincrossoverb"), innerBetweenPoints, 0);
    innerRight->setNext(innerLeft);

    innerLeft->setPrev(innerRight);
    innerLeft->setNext(pCtrl->getPoint("upmaincrossoverb"), 0, innerCenter);

    innerCenter->setPrev(pCtrl->getPoint("upmaincrossoverb"), outerToInnerLeft, innerLeft);
    innerCenter->setNext(dummyInner);

    innerToStation->setPrev(pCtrl->getPoint("stationentrancecrossovera"), 0, innerBetweenPoints);
    innerToStation->setNext(pCtrl->getPoint("stationentrancecrossoverb"), 0, stationOuterBetweenPoints);

    ///////
    dummyStationOuter->setNext(pCtrl->getPoint("downstationcrossovera"), stationOuterBetweenPoints, 0);
    dummyStationOuter->setPrev(stationOuterCenter);

    stationOuterBetweenPoints->setPrev(pCtrl->getPoint("downstationcrossovera"), dummyStationOuter, stationOuterToInnerRight);
    stationOuterBetweenPoints->setNext(pCtrl->getPoint("stationentrancecrossoverb"), stationOuterRight, innerToStation);

    stationOuterRight->setPrev(pCtrl->getPoint("stationentrancecrossoverb"), stationOuterBetweenPoints, 0);
    stationOuterRight->setNext(pCtrl->getPoint("downsiding1"), dummyRightBetweenSidings, stationSidingRight1);

    dummyRightBetweenSidings->setPrev(pCtrl->getPoint("downsiding1"), stationOuterRight, 0);
    dummyRightBetweenSidings->setNext(pCtrl->getPoint("downsiding2"), stationSidingRight3, stationSidingRight2);

    stationSidingRight1->setPrev(pCtrl->getPoint("downsiding1"), 0, stationOuterRight);
    stationSidingRight2->setPrev(pCtrl->getPoint("downsiding2"), 0, dummyRightBetweenSidings);
    stationSidingRight3->setPrev(pCtrl->getPoint("downsiding2"), dummyRightBetweenSidings, 0);

    stationOuterLeft->setNext(pCtrl->getPoint("upstationcrossovera"), stationOuterToInnerLeft, stationOuterCenter);

    stationOuterCenter->setNext(dummyStationOuter);
    stationOuterCenter->setPrev(pCtrl->getPoint("upstationcrossovera"), 0, stationOuterLeft);

    stationOuterToInnerLeft->setPrev(pCtrl->getPoint("upstationcrossovera"), stationOuterLeft, 0);
    stationOuterToInnerLeft->setNext(pCtrl->getPoint("upstationcrossoverb"), stationInnerCenter, 0);

    stationOuterToInnerRight->setPrev(pCtrl->getPoint("downstationcrossovera"), 0, stationOuterBetweenPoints);
    stationOuterToInnerRight->setNext(pCtrl->getPoint("downstationcrossoverb"), 0, dummyStationInner);

    //////

    dummyStationInner->setNext(pCtrl->getPoint("downstationcrossoverb"), stationInnerRight, stationOuterToInnerRight);
    dummyStationInner->setPrev(stationInnerCenter);

    stationInnerRight->setPrev(pCtrl->getPoint("downstationcrossoverb"), dummyStationInner, 0);

    stationInnerCenter->setPrev(pCtrl->getPoint("upstationcrossoverb"), stationOuterToInnerLeft, dummyLeftBetweenPoints);
    stationInnerCenter->setNext(dummyStationInner);


    dummyLeftBetweenPoints->setPrev(pCtrl->getPoint("upsiding1"), stationSidingLeft1, dummyLeftBetweenSidings);
    dummyLeftBetweenPoints->setNext(pCtrl->getPoint("upstationcrossoverb"), 0, stationInnerCenter);

    dummyLeftBetweenSidings->setPrev(pCtrl->getPoint("upmaincrossovera"), stationSidingLeft2, stationSidingLeft3);
    dummyLeftBetweenSidings->setNext(pCtrl->getPoint("upsiding1"), 0, dummyLeftBetweenPoints);

    stationSidingLeft1->setNext(pCtrl->getPoint("upsiding1"), dummyLeftBetweenPoints, 0);
    stationSidingLeft2->setNext(pCtrl->getPoint("upmaincrossovera"), dummyLeftBetweenPoints, 0);
    stationSidingLeft3->setNext(pCtrl->getPoint("upmaincrossovera"), 0, dummyLeftBetweenPoints);

    m_AllNodes.insert("dummyOuter", dummyOuter);
    m_AllNodes.insert("outerRight", outerRight);
    m_AllNodes.insert("outerLeft", outerLeft);
    m_AllNodes.insert("outerCenter", outerCenter);
    m_AllNodes.insert("outerToInnerLeft", outerToInnerLeft);
    m_AllNodes.insert("outerToInnerRight", outerToInnerRight);

    m_AllNodes.insert("dummyInner", dummyInner);
    m_AllNodes.insert("innerBetweenPoints", innerBetweenPoints);
    m_AllNodes.insert("innerRight", innerRight);
    m_AllNodes.insert("innerLeft", innerLeft);
    m_AllNodes.insert("innerCenter", innerCenter);
    m_AllNodes.insert("innerToStation", innerToStation);

    m_AllNodes.insert("dummyStationOuter", dummyStationOuter);
    m_AllNodes.insert("stationOuterBetweenPoints", stationOuterBetweenPoints);
    m_AllNodes.insert("stationOuterRight", stationOuterRight);
    m_AllNodes.insert("stationOuterLeft", stationOuterLeft);
    m_AllNodes.insert("stationOuterCenter", stationOuterCenter);
    m_AllNodes.insert("stationSidingRight1", stationSidingRight1);
    m_AllNodes.insert("dummyRightBetweenSidings", dummyRightBetweenSidings);

    m_AllNodes.insert("stationSidingRight2", stationSidingRight2);
    m_AllNodes.insert("stationSidingRight3", stationSidingRight3);
    m_AllNodes.insert("stationOuterToInnerLeft", stationOuterToInnerLeft);
    m_AllNodes.insert("stationOuterToInnerRight", stationOuterToInnerRight);

    m_AllNodes.insert("dummyStationInner", dummyStationInner);
    m_AllNodes.insert("stationInnerRight", stationInnerRight);
    m_AllNodes.insert("stationInnerCenter", stationInnerCenter);
    m_AllNodes.insert("dummyLeftBetweenPoints", dummyLeftBetweenPoints);
    m_AllNodes.insert("stationSidingLeft1", stationSidingLeft1);
    m_AllNodes.insert("dummyLeftBetweenSidings", dummyLeftBetweenSidings);
    m_AllNodes.insert("stationSidingLeft2", stationSidingLeft2);
    m_AllNodes.insert("stationSidingLeft3", stationSidingLeft3);

    LayoutNode* pOuterController = new LayoutNode();
    LayoutNode* pInnerController = new LayoutNode();
    LayoutNode* pOuterStationController = new LayoutNode();
    LayoutNode* pInnerStationController = new LayoutNode();

    pOuterController->setNext(dummyOuter);
    pOuterController->setPrev(outerCenter);

    pInnerController->setNext(dummyInner);
    pInnerController->setPrev(innerCenter);

    pOuterStationController->setNext(dummyStationOuter);
    pOuterStationController->setPrev(stationOuterCenter);

    pInnerStationController->setNext(dummyStationInner);
    pInnerStationController->setPrev(stationInnerCenter);

    m_ControlNodes.insert(pCtrl->getController("outerloop"), pOuterController);
    m_ControlNodes.insert(pCtrl->getController("innerloop"), pInnerController);
    m_ControlNodes.insert(pCtrl->getController("stationouter"), pOuterStationController);
    m_ControlNodes.insert(pCtrl->getController("stationinner"), pInnerStationController);

    refresh();
}

PanelBoard::~PanelBoard()
{
    qDeleteAll(m_AllNodes);
    qDeleteAll(m_ControlNodes);
}

void PanelBoard::refresh()
{
    QHash<QByteArray, LayoutNode*>::iterator i = m_AllNodes.begin();
    while (i!=m_AllNodes.end())
    {
        i.value()->setState(0);
        ++i;
    }

    QHash<SpeedController*, LayoutNode*>::iterator ctrl = m_ControlNodes.begin();
    while (ctrl!=m_ControlNodes.end())
    {
        const int id = ctrl.key()->id();
        updateNode(ctrl.value()->next(), id);
        updateNode(ctrl.value()->prev(), id);
        ++ctrl;
    }
}

int PanelBoard::getLightState(const QByteArray &lightName) const
{
    if (m_AllNodes.contains(lightName))
    {
        return m_AllNodes.value(lightName)->state();
    }

    return 0;
}

QList<QByteArray> PanelBoard::allNodes() const
{
    return m_AllNodes.keys();
}

void PanelBoard::updateNode(LayoutNode *pNode, int value)
{
    if (pNode)
    {
        if (pNode->state()!=value)
        {
            pNode->setState(value);
            updateNode(pNode->next(), value);
            updateNode(pNode->prev(), value);
        }
    }
}

