#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QPainter>

class GraphicsItem;

class Arrow: public QGraphicsLineItem
{
public:
    enum { Type = UserType +4 };

    Arrow(GraphicsItem *startItem, GraphicsItem *endItem, QGraphicsItem *parent = nullptr);

    int type() const override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color);
    GraphicsItem *startItem() const;
    GraphicsItem *endItem() const;

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    GraphicsItem *myStartItem;
    GraphicsItem *myEndItem;
    QPolygonF arrowHead;
    QColor myColor = Qt::black;
};
#endif // ARROW_H
