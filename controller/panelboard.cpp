#include "panelboard.h"

#include "jsonkeys.h"

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


    dummyOuter->setNext(pCtrl->getPoint(JsonKeys::downMainCrossoverA()), outerRight, 0);
    dummyOuter->setPrev(outerCenter);

    outerRight->setPrev(pCtrl->getPoint(JsonKeys::downMainCrossoverA()), dummyOuter, outerToInnerRight);
    outerRight->setNext(outerLeft);

    outerLeft->setPrev(outerRight);
    outerLeft->setNext(pCtrl->getPoint(JsonKeys::upMainCrossoverA()), outerToInnerLeft, outerCenter);

    outerCenter->setPrev(pCtrl->getPoint(JsonKeys::upMainCrossoverA()), 0, outerLeft);
    outerCenter->setNext(dummyOuter);

    outerToInnerLeft->setPrev(pCtrl->getPoint(JsonKeys::upMainCrossoverA()), outerLeft, 0);
    outerToInnerLeft->setNext(pCtrl->getPoint(JsonKeys::upMainCrossoverB()), innerCenter, 0);

    outerToInnerRight->setPrev(pCtrl->getPoint(JsonKeys::downMainCrossoverA()), 0, outerRight);
    outerToInnerRight->setNext(pCtrl->getPoint(JsonKeys::downMainCrossoverB()), 0, innerBetweenPoints);

    //////

    dummyInner->setNext(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverA()), innerBetweenPoints, 0);
    dummyInner->setPrev(innerCenter);

    innerBetweenPoints->setPrev(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverA()), dummyInner, innerToStation);
    innerBetweenPoints->setNext(pCtrl->getPoint(JsonKeys::downMainCrossoverB()), innerRight, outerToInnerRight);

    innerRight->setPrev(pCtrl->getPoint(JsonKeys::downMainCrossoverB()), innerBetweenPoints, 0);
    innerRight->setNext(innerLeft);

    innerLeft->setPrev(innerRight);
    innerLeft->setNext(pCtrl->getPoint(JsonKeys::upMainCrossoverB()), 0, innerCenter);

    innerCenter->setPrev(pCtrl->getPoint(JsonKeys::upMainCrossoverB()), outerToInnerLeft, innerLeft);
    innerCenter->setNext(dummyInner);

    innerToStation->setPrev(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverA()), 0, innerBetweenPoints);
    innerToStation->setNext(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverB()), 0, stationOuterBetweenPoints);

    ///////
    dummyStationOuter->setNext(pCtrl->getPoint(JsonKeys::downStationCrossoverA()), stationOuterBetweenPoints, 0);
    dummyStationOuter->setPrev(stationOuterCenter);

    stationOuterBetweenPoints->setPrev(pCtrl->getPoint(JsonKeys::downStationCrossoverA()), dummyStationOuter, stationOuterToInnerRight);
    stationOuterBetweenPoints->setNext(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverB()), stationOuterRight, innerToStation);

    stationOuterRight->setPrev(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverB()), stationOuterBetweenPoints, 0);
    stationOuterRight->setNext(pCtrl->getPoint(JsonKeys::downSiding1()), dummyRightBetweenSidings, stationSidingRight1);

    dummyRightBetweenSidings->setPrev(pCtrl->getPoint(JsonKeys::downSiding1()), stationOuterRight, 0);
    dummyRightBetweenSidings->setNext(pCtrl->getPoint(JsonKeys::downSiding2()), stationSidingRight3, stationSidingRight2);

    stationSidingRight1->setPrev(pCtrl->getPoint(JsonKeys::downSiding1()), 0, stationOuterRight);
    stationSidingRight2->setPrev(pCtrl->getPoint(JsonKeys::downSiding2()), 0, dummyRightBetweenSidings);
    stationSidingRight3->setPrev(pCtrl->getPoint(JsonKeys::downSiding2()), dummyRightBetweenSidings, 0);

    stationOuterLeft->setNext(pCtrl->getPoint(JsonKeys::upStationCrossoverA()), stationOuterToInnerLeft, stationOuterCenter);

    stationOuterCenter->setNext(dummyStationOuter);
    stationOuterCenter->setPrev(pCtrl->getPoint(JsonKeys::upStationCrossoverA()), 0, stationOuterLeft);

    stationOuterToInnerLeft->setPrev(pCtrl->getPoint(JsonKeys::upStationCrossoverA()), stationOuterLeft, 0);
    stationOuterToInnerLeft->setNext(pCtrl->getPoint(JsonKeys::upStationCrossoverB()), stationInnerCenter, 0);

    stationOuterToInnerRight->setPrev(pCtrl->getPoint(JsonKeys::downStationCrossoverA()), 0, stationOuterBetweenPoints);
    stationOuterToInnerRight->setNext(pCtrl->getPoint(JsonKeys::downStationCrossoverB()), 0, dummyStationInner);

    //////

    dummyStationInner->setNext(pCtrl->getPoint(JsonKeys::downStationCrossoverB()), stationInnerRight, stationOuterToInnerRight);
    dummyStationInner->setPrev(stationInnerCenter);

    stationInnerRight->setPrev(pCtrl->getPoint(JsonKeys::downStationCrossoverB()), dummyStationInner, 0);

    stationInnerCenter->setPrev(pCtrl->getPoint(JsonKeys::upStationCrossoverB()), stationOuterToInnerLeft, dummyLeftBetweenPoints);
    stationInnerCenter->setNext(dummyStationInner);


    dummyLeftBetweenPoints->setPrev(pCtrl->getPoint(JsonKeys::upSiding1()), stationSidingLeft1, dummyLeftBetweenSidings);
    dummyLeftBetweenPoints->setNext(pCtrl->getPoint(JsonKeys::upStationCrossoverB()), 0, stationInnerCenter);

    dummyLeftBetweenSidings->setPrev(pCtrl->getPoint(JsonKeys::upMainCrossoverA()), stationSidingLeft2, stationSidingLeft3);
    dummyLeftBetweenSidings->setNext(pCtrl->getPoint(JsonKeys::upSiding1()), 0, dummyLeftBetweenPoints);

    stationSidingLeft1->setNext(pCtrl->getPoint(JsonKeys::upSiding1()), dummyLeftBetweenPoints, 0);
    stationSidingLeft2->setNext(pCtrl->getPoint(JsonKeys::upMainCrossoverA()), dummyLeftBetweenPoints, 0);
    stationSidingLeft3->setNext(pCtrl->getPoint(JsonKeys::upMainCrossoverA()), 0, dummyLeftBetweenPoints);

    m_AllNodes.insert(JsonKeys::dummyOuter(), dummyOuter);
    m_AllNodes.insert(JsonKeys::outerRight(), outerRight);
    m_AllNodes.insert(JsonKeys::outerLeft(), outerLeft);
    m_AllNodes.insert(JsonKeys::outerCenter(), outerCenter);
    m_AllNodes.insert(JsonKeys::outerToInnerLeft(), outerToInnerLeft);
    m_AllNodes.insert(JsonKeys::outerToInnerRight(), outerToInnerRight);

    m_AllNodes.insert(JsonKeys::dummyInner(), dummyInner);
    m_AllNodes.insert(JsonKeys::innerBetweenPoints(), innerBetweenPoints);
    m_AllNodes.insert(JsonKeys::innerRight(), innerRight);
    m_AllNodes.insert(JsonKeys::innerLeft(), innerLeft);
    m_AllNodes.insert(JsonKeys::innerCenter(), innerCenter);
    m_AllNodes.insert(JsonKeys::innerToStation(), innerToStation);

    m_AllNodes.insert(JsonKeys::dummyStationOuter(), dummyStationOuter);
    m_AllNodes.insert(JsonKeys::stationOuterBetweenPoints(), stationOuterBetweenPoints);
    m_AllNodes.insert(JsonKeys::stationOuterRight(), stationOuterRight);
    m_AllNodes.insert(JsonKeys::stationOuterLeft(), stationOuterLeft);
    m_AllNodes.insert(JsonKeys::stationOuterCenter(), stationOuterCenter);
    m_AllNodes.insert(JsonKeys::stationSidingRight1(), stationSidingRight1);
    m_AllNodes.insert(JsonKeys::dummyRightBetweenSidings(), dummyRightBetweenSidings);

    m_AllNodes.insert(JsonKeys::stationSidingRight2(), stationSidingRight2);
    m_AllNodes.insert(JsonKeys::stationSidingRight3(), stationSidingRight3);
    m_AllNodes.insert(JsonKeys::stationOuterToInnerLeft(), stationOuterToInnerLeft);
    m_AllNodes.insert(JsonKeys::stationOuterToInnerRight(), stationOuterToInnerRight);

    m_AllNodes.insert(JsonKeys::dummyStationInner(), dummyStationInner);
    m_AllNodes.insert(JsonKeys::stationInnerRight(), stationInnerRight);
    m_AllNodes.insert(JsonKeys::stationInnerCenter(), stationInnerCenter);
    m_AllNodes.insert(JsonKeys::dummyLeftBetweenPoints(), dummyLeftBetweenPoints);
    m_AllNodes.insert(JsonKeys::stationSidingLeft1(), stationSidingLeft1);
    m_AllNodes.insert(JsonKeys::dummyLeftBetweenSidings(), dummyLeftBetweenSidings);
    m_AllNodes.insert(JsonKeys::stationSidingLeft2(), stationSidingLeft2);
    m_AllNodes.insert(JsonKeys::stationSidingLeft3(), stationSidingLeft3);

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

    m_ControlNodes.insert(pCtrl->getController(JsonKeys::outerLoop()), pOuterController);
    m_ControlNodes.insert(pCtrl->getController(JsonKeys::innerLoop()), pInnerController);
    m_ControlNodes.insert(pCtrl->getController(JsonKeys::stationOuter()), pOuterStationController);
    m_ControlNodes.insert(pCtrl->getController(JsonKeys::stationInner()), pInnerStationController);

    refresh();
}

PanelBoard::~PanelBoard()
{
    qDeleteAll(m_AllNodes);
    qDeleteAll(m_ControlNodes);
}

void PanelBoard::refresh()
{
    QHash<QString, LayoutNode*>::iterator i = m_AllNodes.begin();
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

int PanelBoard::getLightState(const QString &lightName) const
{
    if (m_AllNodes.contains(lightName))
    {
        return m_AllNodes.value(lightName)->state();
    }

    return 0;
}

QList<QString> PanelBoard::allNodes() const
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

