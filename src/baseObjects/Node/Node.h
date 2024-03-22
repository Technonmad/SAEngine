#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>

class GraphWidget;
class Edge;

class Node: public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget);

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

#endif // NODE_H
