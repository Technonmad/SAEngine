#ifndef WAREHOUSEITEM_H
#define WAREHOUSEITEM_H

#include "Arrow/Arrow.h"
#include <QTextEdit>
#include <QVariant>
#include <Item/GraphicsItem.h>

class WarehouseItem : public GraphicsItem
{
    Q_OBJECT
public:
    WarehouseItem(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    ~WarehouseItem();

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
//    void sendMessage(DiagramEventType event, const QString &message);
    void fireEvent();
    void startProcessEvent();
    void continueProcessEvent();
    void endProcessEvent();
    void startDeliveringEvent();
    void continueDeliveringEvent();
    void endDeliveringEvent();

public slots:
    void receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message) override;
    void startEvents();
    void onFireEvent();
    void onStartProcessEvent();
    void onEndProcessEvent();
    void onContinueProcessEvent();
    void onStartDeliveringEvent();
    void onContinueDeliveringEvent();
    void onEndDeliveringEvent();

private:
    QTimer *eventTimer;
    QTimer *processTimer;
    bool oldProcessState;
    bool oldEventState;

public:
    DiagramAgentState state;
};

#endif // WAREHOUSEITEM_H
