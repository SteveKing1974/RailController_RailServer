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
    LayoutNode* stationSidingRight1Entrance = new LayoutNode();
    LayoutNode* dummyRightBetweenSidings = new LayoutNode();
    LayoutNode* stationSidingRight2 = new LayoutNode();
    LayoutNode* stationSidingRight3Entrance = new LayoutNode();
    LayoutNode* stationSidingRight3 = new LayoutNode();

    LayoutNode* stationOuterToInnerLeft = new LayoutNode();
    LayoutNode* stationOuterToInnerRight = new LayoutNode();

    LayoutNode* dummyStationInner = new LayoutNode();
    LayoutNode* stationInnerRight = new LayoutNode();
    LayoutNode* stationInnerRightSiding = new LayoutNode();
    LayoutNode* stationInnerCenter = new LayoutNode();

    LayoutNode* dummyLeftBetweenPoints = new LayoutNode();
    LayoutNode* stationSidingLeft1 = new LayoutNode();
    LayoutNode* dummyLeftBetweenSidings = new LayoutNode();
    LayoutNode* stationSidingLeft2 = new LayoutNode();
    LayoutNode* stationSidingLeft3 = new LayoutNode();
    LayoutNode* stationSidingLeft3Entrance = new LayoutNode();

    //stationSidingRight3Entrance

    dummyOuter->setNext(pCtrl->getPoint(JsonKeys::downMainCrossoverA()), outerRight, nullptr);
    dummyOuter->setPrev(outerCenter);

    outerRight->setPrev(pCtrl->getPoint(JsonKeys::downMainCrossoverA()), dummyOuter, outerToInnerRight);
    outerRight->setNext(outerLeft);

    outerLeft->setPrev(outerRight);
    outerLeft->setNext(pCtrl->getPoint(JsonKeys::upMainCrossoverA()), outerToInnerLeft, outerCenter);

    outerCenter->setPrev(pCtrl->getPoint(JsonKeys::upMainCrossoverA()), nullptr, outerLeft);
    outerCenter->setNext(dummyOuter);

    outerToInnerLeft->setPrev(pCtrl->getPoint(JsonKeys::upMainCrossoverA()), outerLeft, nullptr);
    outerToInnerLeft->setNext(pCtrl->getPoint(JsonKeys::upMainCrossoverB()), innerCenter, nullptr);

    outerToInnerRight->setPrev(pCtrl->getPoint(JsonKeys::downMainCrossoverA()), nullptr, outerRight);
    outerToInnerRight->setNext(pCtrl->getPoint(JsonKeys::downMainCrossoverB()), nullptr, innerBetweenPoints);

    //////

    dummyInner->setNext(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverA()), innerBetweenPoints, nullptr);
    dummyInner->setPrev(innerCenter);

    innerBetweenPoints->setPrev(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverA()), dummyInner, innerToStation);
    innerBetweenPoints->setNext(pCtrl->getPoint(JsonKeys::downMainCrossoverB()), innerRight, outerToInnerRight);

    innerRight->setPrev(pCtrl->getPoint(JsonKeys::downMainCrossoverB()), innerBetweenPoints, nullptr);
    innerRight->setNext(innerLeft);

    innerLeft->setPrev(innerRight);
    innerLeft->setNext(pCtrl->getPoint(JsonKeys::upMainCrossoverB()), nullptr, innerCenter);

    innerCenter->setPrev(pCtrl->getPoint(JsonKeys::upMainCrossoverB()), outerToInnerLeft, innerLeft);
    innerCenter->setNext(dummyInner);

    innerToStation->setPrev(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverA()), nullptr, innerBetweenPoints);
    innerToStation->setNext(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverB()), nullptr, stationOuterBetweenPoints);

    ///////
    dummyStationOuter->setNext(pCtrl->getPoint(JsonKeys::downStationCrossoverA()), stationOuterBetweenPoints, nullptr);
    dummyStationOuter->setPrev(stationOuterCenter);

    stationOuterBetweenPoints->setPrev(pCtrl->getPoint(JsonKeys::downStationCrossoverA()), dummyStationOuter, stationOuterToInnerRight);
    stationOuterBetweenPoints->setNext(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverB()), stationOuterRight, innerToStation);

    stationOuterRight->setPrev(pCtrl->getPoint(JsonKeys::stationEntranceCrossoverB()), stationOuterBetweenPoints, nullptr);
    stationOuterRight->setNext(pCtrl->getPoint(JsonKeys::downSiding1()), dummyRightBetweenSidings, stationSidingRight1Entrance);

    dummyRightBetweenSidings->setPrev(pCtrl->getPoint(JsonKeys::downSiding1()), stationOuterRight, nullptr);
    dummyRightBetweenSidings->setNext(pCtrl->getPoint(JsonKeys::downSiding2()), stationSidingRight3Entrance, stationSidingRight2);

    stationSidingRight1Entrance->setPrev(pCtrl->getPoint(JsonKeys::downSiding1()), stationOuterRight, nullptr);
    stationSidingRight1Entrance->setNext(pCtrl->getIsolator(JsonKeys::bottomSidingDown()), stationSidingRight1);

    stationSidingRight3Entrance->setPrev(pCtrl->getPoint(JsonKeys::downSiding2()), dummyRightBetweenSidings, nullptr);
    stationSidingRight3Entrance->setNext(pCtrl->getIsolator(JsonKeys::topSidingDown()), stationSidingRight3);

    stationSidingRight1->setPrev(pCtrl->getIsolator(JsonKeys::bottomSidingDown()), stationSidingRight1Entrance);

    stationSidingRight2->setPrev(pCtrl->getPoint(JsonKeys::downSiding2()), nullptr, dummyRightBetweenSidings);
    stationSidingRight3->setPrev(pCtrl->getIsolator(JsonKeys::topSidingDown()), stationSidingRight3Entrance);

    stationOuterLeft->setNext(pCtrl->getPoint(JsonKeys::upStationCrossoverA()), stationOuterToInnerLeft, stationOuterCenter);

    stationOuterCenter->setNext(dummyStationOuter);
    stationOuterCenter->setPrev(pCtrl->getPoint(JsonKeys::upStationCrossoverA()), nullptr, stationOuterLeft);

    stationOuterToInnerLeft->setPrev(pCtrl->getPoint(JsonKeys::upStationCrossoverA()), stationOuterLeft, nullptr);
    stationOuterToInnerLeft->setNext(pCtrl->getPoint(JsonKeys::upStationCrossoverB()), stationInnerCenter, nullptr);

    stationOuterToInnerRight->setPrev(pCtrl->getPoint(JsonKeys::downStationCrossoverA()), nullptr, stationOuterBetweenPoints);
    stationOuterToInnerRight->setNext(pCtrl->getPoint(JsonKeys::downStationCrossoverB()), nullptr, dummyStationInner);

    //////

    dummyStationInner->setNext(pCtrl->getPoint(JsonKeys::downStationCrossoverB()), stationInnerRight, stationOuterToInnerRight);
    dummyStationInner->setPrev(stationInnerCenter);

    stationInnerRight->setPrev(pCtrl->getPoint(JsonKeys::downStationCrossoverB()), dummyStationInner, nullptr);
    stationInnerRight->setNext(pCtrl->getIsolator(JsonKeys::stationSidingDown()), stationInnerRightSiding);

    stationInnerRightSiding->setPrev(pCtrl->getIsolator(JsonKeys::stationSidingDown()), stationInnerRight);

    stationInnerCenter->setPrev(pCtrl->getPoint(JsonKeys::upStationCrossoverB()), stationOuterToInnerLeft, dummyLeftBetweenPoints);
    stationInnerCenter->setNext(dummyStationInner);


    dummyLeftBetweenPoints->setPrev(pCtrl->getPoint(JsonKeys::upSiding1()), stationSidingLeft1, dummyLeftBetweenSidings);
    dummyLeftBetweenPoints->setNext(pCtrl->getPoint(JsonKeys::upStationCrossoverB()), nullptr, stationInnerCenter);

    dummyLeftBetweenSidings->setPrev(pCtrl->getPoint(JsonKeys::upSiding2()), stationSidingLeft2, stationSidingLeft3Entrance);
    dummyLeftBetweenSidings->setNext(pCtrl->getPoint(JsonKeys::upSiding1()), nullptr, dummyLeftBetweenPoints);

    stationSidingLeft3Entrance->setNext(pCtrl->getPoint(JsonKeys::upSiding2()), dummyLeftBetweenSidings, nullptr);
    stationSidingLeft3Entrance->setPrev(pCtrl->getIsolator(JsonKeys::topSidingUp()), stationSidingLeft3);

    stationSidingLeft1->setNext(pCtrl->getPoint(JsonKeys::upSiding1()), dummyLeftBetweenPoints, nullptr);
    stationSidingLeft2->setNext(pCtrl->getPoint(JsonKeys::upSiding2()), dummyLeftBetweenSidings, nullptr);
    stationSidingLeft3->setNext(pCtrl->getIsolator(JsonKeys::topSidingUp()), stationSidingLeft3Entrance);

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
    m_AllNodes.insert(JsonKeys::stationSidingRight1Entrance(), stationSidingRight1Entrance);
    m_AllNodes.insert(JsonKeys::dummyRightBetweenSidings(), dummyRightBetweenSidings);

    m_AllNodes.insert(JsonKeys::stationSidingRight2(), stationSidingRight2);
    m_AllNodes.insert(JsonKeys::stationSidingRight3(), stationSidingRight3);
    m_AllNodes.insert(JsonKeys::stationSidingRight3Entrance(), stationSidingRight3Entrance);
    m_AllNodes.insert(JsonKeys::stationOuterToInnerLeft(), stationOuterToInnerLeft);
    m_AllNodes.insert(JsonKeys::stationOuterToInnerRight(), stationOuterToInnerRight);

    m_AllNodes.insert(JsonKeys::dummyStationInner(), dummyStationInner);
    m_AllNodes.insert(JsonKeys::stationInnerRight(), stationInnerRight);
    m_AllNodes.insert(JsonKeys::stationInnerRightSiding(), stationInnerRightSiding);
    m_AllNodes.insert(JsonKeys::stationInnerCenter(), stationInnerCenter);
    m_AllNodes.insert(JsonKeys::dummyLeftBetweenPoints(), dummyLeftBetweenPoints);
    m_AllNodes.insert(JsonKeys::stationSidingLeft1(), stationSidingLeft1);
    m_AllNodes.insert(JsonKeys::dummyLeftBetweenSidings(), dummyLeftBetweenSidings);
    m_AllNodes.insert(JsonKeys::stationSidingLeft2(), stationSidingLeft2);
    m_AllNodes.insert(JsonKeys::stationSidingLeft3(), stationSidingLeft3);
    m_AllNodes.insert(JsonKeys::stationSidingLeft3Entrance(), stationSidingLeft3Entrance);

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

    m_ControlNodes.insert(JsonKeys::outerLoop(), pOuterController);
    m_ControlNodes.insert(JsonKeys::innerLoop(), pInnerController);
    m_ControlNodes.insert(JsonKeys::stationOuter(), pOuterStationController);
    m_ControlNodes.insert(JsonKeys::stationInner(), pInnerStationController);

    refresh();
}

PanelBoard::~PanelBoard()
{
    qDeleteAll(m_AllNodes);
    qDeleteAll(m_ControlNodes);
}

void PanelBoard::refresh()
{
    if (0)
    {
        QStringList allNodeNames = m_AllNodes.keys();
        allNodeNames.sort();
        foreach (const QString& s, allNodeNames)
        {
            m_AllNodes.value(s)->show(m_AllNodes);
        }
    }

    QHash<QString, LayoutNode*>::iterator i = m_AllNodes.begin();
    while (i!=m_AllNodes.end())
    {
        i.value()->setNodeController("");
        ++i;
    }

    QHash<QString, LayoutNode*>::iterator ctrl = m_ControlNodes.begin();
    while (ctrl!=m_ControlNodes.end())
    {
        //qDebug() << "---" << ctrl.key();
        updateNode(ctrl.value()->next(), ctrl.key());
        updateNode(ctrl.value()->prev(), ctrl.key());
        ++ctrl;
    }
}

QString PanelBoard::nodeController(const QString &nodeName) const
{
    if (m_AllNodes.contains(nodeName))
    {
        return m_AllNodes.value(nodeName)->nodeController();
    }

    return QString();
}

QList<QString> PanelBoard::allNodes() const
{
    return m_AllNodes.keys();
}

void PanelBoard::updateNode(LayoutNode *pNode, const QString& nodeController)
{
    if (pNode)
    {
        if (pNode->nodeController()!=nodeController)
        {
            //qDebug() << m_AllNodes.key(pNode);
            pNode->setNodeController(nodeController);
            updateNode(pNode->next(), nodeController);
            updateNode(pNode->prev(), nodeController);
        }
    }
}

