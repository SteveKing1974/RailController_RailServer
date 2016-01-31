#include "layoutnode.h"

LayoutNode::LayoutNode() :
    m_PrevSwitch(0),
    m_NextSwitch(0),
    m_PrevPoint(0),
    m_NextPoint(0),
    m_PrevNodeLeft(0),
    m_PrevNodeRight(0),
    m_NextNodeLeft(0),
    m_NextNodeRight(0)
{

}


void LayoutNode::setNext(LayoutNode *node)
{
    m_NextNodeLeft = node;
}

void LayoutNode::setNext(const SwitchController *switchCtrl, LayoutNode *node)
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

void LayoutNode::setPrev(const SwitchController *switchCtrl, LayoutNode *node)
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

int LayoutNode::state() const
{
    return m_State;
}

void LayoutNode::setState(int newState)
{
    m_State = newState;
}

LayoutNode *LayoutNode::calcOutput(const SwitchController *pSw, const BasePointController *pPnt, LayoutNode *pLeft, LayoutNode *pRight) const
{
    if (pSw==0)
    {
        if (pPnt==0)
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
        if (pSw->state()==SwitchController::eSwitchClosed)
        {
            return pLeft;
        }

        return pRight;
    }
}
