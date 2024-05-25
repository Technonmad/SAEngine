#ifndef FIRESENSOR_H
#define FIRESENSOR_H

#include "Arrow/Arrow.h"
#include <QTextEdit>
#include <QVariant>
#include <Item/GraphicsItem.h>

class Firesensor : public GraphicsItem
{
    Q_OBJECT
public:
    Firesensor(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    ~Firesensor();

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

public slots:
    void receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message) override;

public:
    DiagramAgentState state;
};

#endif // FIRESENSOR_H
