#ifndef LAYOUTNODE_H
#define LAYOUTNODE_H

#include <QByteArray>

#include "basepointcontroller.h"
#include "switchcontroller.h"

class LayoutNode
{
public:
    LayoutNode();

    void setNext(LayoutNode* node);
    void setNext(const SwitchController* switchCtrl, LayoutNode* node);
    void setNext(const BasePointController* pointCtl, LayoutNode* leftNode, LayoutNode* rightNode);

    void setPrev(LayoutNode* node);
    void setPrev(const SwitchController* switchCtrl, LayoutNode* node);
    void setPrev(const BasePointController* pointCtl, LayoutNode* leftNode, LayoutNode* rightNode);

    LayoutNode* prev();
    LayoutNode* next();

    int state() const;
    void setState(int newState);

private:
    const SwitchController* m_PrevSwitch;
    const SwitchController* m_NextSwitch;
    const BasePointController* m_PrevPoint;
    const BasePointController* m_NextPoint;

    LayoutNode* m_PrevNodeLeft;
    LayoutNode* m_PrevNodeRight;
    LayoutNode* m_NextNodeLeft;
    LayoutNode* m_NextNodeRight;

    int m_State;

    LayoutNode* calcOutput(const SwitchController* pSw, const BasePointController* pPnt, LayoutNode* pLeft, LayoutNode* pRight) const;
};

#endif // LAYOUTNODE_H
