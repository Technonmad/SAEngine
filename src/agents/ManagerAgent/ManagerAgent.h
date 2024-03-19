#ifndef MANAGERAGENT_H
#define MANAGERAGENT_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include "Edge/Edge.h"
#include "graphWidget/GraphWidget.h"

class ManagerAgent: public QGraphicsItem
{
public:
    ManagerAgent(GraphWidget *graphWidget);

    void addEdge(Edge *edge);

    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };

    int type() const override { return Type; }

    void calculateForces();
    bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QVector<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
};

#endif // MANAGERAGENT_H
