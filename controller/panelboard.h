#ifndef PANELBOARD_H
#define PANELBOARD_H

#include "speedcontroller.h"
#include "layoutnode.h"
#include "hardwarecontroller.h"

#include <QHash>
#include <QList>
#include <QString>

class PanelBoard
{
public:
    PanelBoard(const HardwareController* pCtrl);
    ~PanelBoard();

    void refresh();

    int getLightState(const QString& lightName) const;

    QList<QString> allNodes() const;

private:
    void updateNode(LayoutNode* pNode, int value);

    QHash<SpeedController*, LayoutNode*> m_ControlNodes;

    QHash<QString, LayoutNode*> m_AllNodes;
};

#endif // PANELBOARD_H
