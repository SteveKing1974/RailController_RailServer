#ifndef LAYOUTNODE_H
#define LAYOUTNODE_H

#include <QByteArray>
#include <QString>

#include "basepointcontroller.h"
#include "isolatorcontroller.h"

class LayoutNode
{
public:
    LayoutNode();

    void setNext(LayoutNode* node);
    void setNext(const IsolatorController* switchCtrl, LayoutNode* node);
    void setNext(const BasePointController* pointCtl, LayoutNode* leftNode, LayoutNode* rightNode);

    void setPrev(LayoutNode* node);
    void setPrev(const IsolatorController* switchCtrl, LayoutNode* node);
    void setPrev(const BasePointController* pointCtl, LayoutNode* leftNode, LayoutNode* rightNode);

    LayoutNode* prev();
    LayoutNode* next();

    QString nodeController() const;
    void setNodeController(const QString& newController);

    void show(const QHash<QString, LayoutNode*>& nameTable) const;

private:
    const IsolatorController* m_PrevSwitch;
    const IsolatorController* m_NextSwitch;
    const BasePointController* m_PrevPoint;
    const BasePointController* m_NextPoint;

    LayoutNode* m_PrevNodeLeft;
    LayoutNode* m_PrevNodeRight;
    LayoutNode* m_NextNodeLeft;
    LayoutNode* m_NextNodeRight;

    QString m_NodeController;

    LayoutNode* calcOutput(const IsolatorController* pSw, const BasePointController* pPnt, LayoutNode* pLeft, LayoutNode* pRight) const;
};

#endif // LAYOUTNODE_H
