#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

/* This is called a "forward declaration".  We use it to tell the compiler that
   the identifier "ManagerAgent" will from now on stand for a class, and this class will be
   defined later.  We will not be able to make any use of "ManagerAgent" before it has been
   defined, but we will at least be able to declare pointers to it. */

class ManagerAgent;

class Edge : public QGraphicsItem
{
public:
    Edge(ManagerAgent *sourceNode, ManagerAgent *destNode);

    ManagerAgent *sourceNode() const;
    ManagerAgent *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    ManagerAgent *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;
};

#endif // EDGE_H
