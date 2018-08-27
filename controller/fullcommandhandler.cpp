#include "fullcommandhandler.h"
#include "jsonkeys.h"

#include <QJsonDocument>

#include <QDebug>

FullCommandHandler::FullCommandHandler(HardwareController *pControl, PanelBoard* pPanel, InterlockHandling *pInterlock) :
    m_pController(pControl),
    m_pPanel(pPanel),
    m_pInterlock(pInterlock)
{
}

QJsonObject FullCommandHandler::getPanelData() const
{
    QJsonObject obj;
    QJsonObject nodes;
    const QList<QString> keys = m_pPanel->allNodes();
    foreach (const QString& key, keys)
    {
        nodes.insert(key, m_pPanel->nodeController(key));
    }

    QJsonObject points;
    const QList<QString> allPoints = m_pController->allPoints();
    foreach (const QString& point, allPoints)
    {
        QJsonObject pt;
        pt.insert(JsonKeys::direction(), m_pController->getPoint(point)->direction());
        pt.insert(JsonKeys::enabled(), m_pController->getPoint(point)->enabled());
        points.insert(point, pt);
    }

    QJsonObject isolators;
    const QList<QString> allIsolators = m_pController->allIsolators();
    foreach (const QString& isolator, allIsolators)
    {
        QJsonObject iso;
        iso.insert(JsonKeys::enabled(), m_pController->getIsolator(isolator)->getState());
        isolators.insert(isolator, iso);
    }

    obj.insert(JsonKeys::nodes(), nodes);
    obj.insert(JsonKeys::points(), points);
    obj.insert(JsonKeys::isolators(), isolators);

    return obj;
}

QJsonObject FullCommandHandler::getControllerData() const
{
    QJsonObject obj;

    foreach (const QString& name, m_pController->allControllers())
    {
        const SpeedController* pCtrl = m_pController->getController(name);
        obj.insert(name, pCtrl->toJson());
    }

    return obj;
}

QJsonObject FullCommandHandler::handleCommand(const QJsonObject& data)
{
    QJsonObject obj;

    if (data.value(JsonKeys::command()) == JsonKeys::get())
    {
        qDebug() << "Get";
        if (data.value(JsonKeys::data()) == JsonKeys::panel())
        {
            obj.insert(JsonKeys::panel(), getPanelData());
        }
        else if (data.value(JsonKeys::data()) == JsonKeys::controller())
        {
            obj.insert(JsonKeys::controller(), getControllerData());
        }
        else
        {
            obj.insert(JsonKeys::error(), QLatin1String("Badly formed get: ") + data.value(JsonKeys::data()).toString());
        }
    }
    else if (data.value(JsonKeys::command()) == JsonKeys::put())
    {
        qDebug() << "Put" << data.value(JsonKeys::data()).toString();

        if (data.value(JsonKeys::data()) == JsonKeys::panel())
        {
            BasePointController* pPoint = m_pController->getPoint(data.value(JsonKeys::points()).toString());

            if (pPoint)
            {
                m_pInterlock->togglePoint(data.value(JsonKeys::points()).toString());
                m_pPanel->refresh();

                obj.insert(JsonKeys::panel(), getPanelData());
            }
            else
            {
                IsolatorController *pIsol = m_pController->getIsolator(data.value(JsonKeys::isolators()).toString());

                if (pIsol)
                {
                    pIsol->toggle();
                    m_pPanel->refresh();

                    obj.insert(JsonKeys::panel(), getPanelData());
                }
                else
                {
                    obj.insert(JsonKeys::error(), QString("Invalid point or isolator: " + data.value(JsonKeys::points()).toString()
                                                          + data.value(JsonKeys::isolators()).toString()));
                }
            }
        }
        else if (data.value(JsonKeys::data()) == JsonKeys::controller())
        {
            if (m_pInterlock->updateController(data))
            {
                obj.insert(JsonKeys::controller(), getControllerData());
            }
            else
            {
                obj.insert(JsonKeys::error(), QLatin1String("Invalid controller: ") + data.value(JsonKeys::controller()).toString());
            }
        }
        else
        {
            obj.insert(JsonKeys::error(), QLatin1String("Badly formed put: ") + data.value(JsonKeys::data()).toString());
        }
    }
    else
    {
        obj.insert(JsonKeys::error(), QLatin1String("Unknown command: ") + data.value(JsonKeys::command()).toString());
    }

    return obj;
}



