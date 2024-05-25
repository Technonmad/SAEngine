#ifndef FIREFIGHTERS_H
#define FIREFIGHTERS_H

#include "Arrow/Arrow.h"
#include <QTextEdit>
#include <QVariant>
#include <Item/GraphicsItem.h>

class Firefighters : public GraphicsItem
{
    Q_OBJECT
public:
    Firefighters(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    ~Firefighters();

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
    void startProcessEvent();
    void endProcessEvent();

public slots:
    void receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message) override;
    void onStartProcessEvent();
    void onEndProcessEvent();

private:
    QTimer *processTimer;
    bool oldProcessState;

public:
    DiagramAgentState state;
};

#endif // FIREFIGHTERS_H
