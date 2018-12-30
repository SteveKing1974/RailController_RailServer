#include "layoutnode.h"
#include <QDebug>

LayoutNode::LayoutNode() :
    m_PrevSwitch(nullptr),
    m_NextSwitch(nullptr),
    m_PrevPoint(nullptr),
    m_NextPoint(nullptr),
    m_PrevNodeLeft(nullptr),
    m_PrevNodeRight(nullptr),
    m_NextNodeLeft(nullptr),
    m_NextNodeRight(nullptr)
{

}


void LayoutNode::setNext(LayoutNode *node)
{
    m_NextNodeLeft = node;
}

void LayoutNode::setNext(const IsolatorController *switchCtrl, LayoutNode *node)
{
    m_NextSwitch = switchCtrl;
    m_NextNodeLeft = node;
}

void LayoutNode::setNext(const BasePointController *pointCtl, LayoutNode *leftNode, LayoutNode *rightNode)
{
    m_NextPoint = pointCtl;
    m_NextNodeLeft = leftNode;
    m_NextNodeRight = rightNode;
}

void LayoutNode::setPrev(LayoutNode *node)
{
    m_PrevNodeLeft = node;
}

void LayoutNode::setPrev(const IsolatorController *switchCtrl, LayoutNode *node)
{
    m_PrevSwitch = switchCtrl;
    m_PrevNodeLeft = node;
}

void LayoutNode::setPrev(const BasePointController *pointCtl, LayoutNode *leftNode, LayoutNode *rightNode)
{
    m_PrevPoint = pointCtl;
    m_PrevNodeLeft = leftNode;
    m_PrevNodeRight = rightNode;
}

LayoutNode* LayoutNode::prev()
{
    return calcOutput(m_PrevSwitch, m_PrevPoint, m_PrevNodeLeft, m_PrevNodeRight);
}

LayoutNode* LayoutNode::next()
{
    return calcOutput(m_NextSwitch, m_NextPoint, m_NextNodeLeft, m_NextNodeRight);
}

QString LayoutNode::nodeController() const
{
    return m_NodeController;
}

void LayoutNode::setNodeController(const QString &newController)
{
    m_NodeController = newController;
}

void LayoutNode::show(const QHash<QString, LayoutNode *> &nameTable) const
{
    qDebug() << nameTable.key(m_PrevNodeLeft, "none") << "\t\t\t" << nameTable.key(m_NextNodeLeft, "none");
    qDebug() << "\t\t" << nameTable.key(const_cast<LayoutNode*>(this), "none");
    qDebug() << nameTable.key(m_PrevNodeRight, "none") << "\t\t\t" << nameTable.key(m_NextNodeRight, "none");
    qDebug() << "  -- ";
}

LayoutNode *LayoutNode::calcOutput(const IsolatorController *pSw, const BasePointController *pPnt, LayoutNode *pLeft, LayoutNode *pRight) const
{
    if (pSw==nullptr)
    {
        if (pPnt==nullptr)
        {
            return pLeft;
        }
        else
        {
            if (pPnt->direction()==BasePointController::ePointLeft)
            {
                return pLeft;
            }
            else
            {
                return pRight;
            }

        }
    }
    else
    {
        if (pSw->state()==IsolatorController::CONNECTED)
        {
            qDebug() << "Connected";
            return pLeft;
        }

        return pRight;
    }
}
