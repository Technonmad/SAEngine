#ifndef DELIVERY_H
#define DELIVERY_H

#include "Arrow/Arrow.h"
#include <QTextEdit>
#include <QVariant>
#include <Item/GraphicsItem.h>

class Delivery : public GraphicsItem
{
    Q_OBJECT
public:
    Delivery(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    ~Delivery();

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void addArrow(Arrow *arrow) override;
    int type() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void removeArrow(Arrow *arrow) override;
    void removeArrows() override;

public:
    void wakeUp() override;
    void pauseAgents() override;
    void continueAgents() override;

signals:
    void goodsReceivedEvent();
    void deliveryIsHere();
    void stopReceiving();
    void continueReceiving();
    void startProcessEvent();

public slots:
    void receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message) override;
    void onStartProcessEvent();
    void onGoodsReceivedEndEvent();
    void startEvents();
    void onStopReceiving();
    void onContinueReceiving();
    void onDeliveryIsHere();

private:
    QTimer *eventTimer;
    QTimer *processTimer;
    bool oldProcessState;
    bool oldEventState;

public:
    DiagramAgentState state;

};

#endif // DELIVERY_H
