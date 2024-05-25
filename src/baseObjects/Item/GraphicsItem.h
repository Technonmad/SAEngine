#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QGraphicsItem>
#include <QMenu>

class Arrow;

class GraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 15 };
    enum DiagramType {
        FireSensor,
        Firefighters,
        Managers,
        Warehouse,
        ProductionLine,
        Delivery,
        Tecnician,
    };
    enum DiagramEventType {
        FireEvent,
        BrakeEvent,
        ProcessStartEvent,
        ProcessContinueEvent,
        ProcessEndEvent,
        RepairEvent,
        FireOutEvent,
        StartDeliveryEvent,
        ContinueDeliveryEvent,
        EndDeliveryEvent,
        DeliveryIsHereEvent,
        DeliveryIsOutEvent,
        DeliveryIsWaiting,
        StartEvent,
    };
    enum DiagramAgentState {
        Working,
        Stopped,
        SendingToDeliver,
        Delivering,
    };

    Q_ENUM(DiagramType)
    Q_ENUM(DiagramEventType)
    Q_ENUM(DiagramAgentState)

    GraphicsItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    virtual ~GraphicsItem(){};

    QRectF boundingRect() const override = 0;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;
    DiagramType diagramType() const;
    virtual void addArrow(Arrow *arrow) = 0;
    virtual int type() const override = 0;
    virtual void removeArrow(Arrow *arrow) = 0;
    virtual void removeArrows() = 0;
    virtual void wakeUp() = 0;
    virtual void pauseAgents() = 0;
    virtual void continueAgents() = 0;
signals:
    void sendMessage(DiagramType type, DiagramEventType event,const QString &message);
public slots:
    virtual void receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message) = 0;

protected:
//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QGraphicsPixmapItem *m_pixmapItem;
//    QGraphicsTextItem *m_textItem;
    QList<Arrow *> arrows;

private:
    DiagramType myDiagramType;
    QMenu *myContextMenu;
};

#endif // GRAPHICSITEM_H
