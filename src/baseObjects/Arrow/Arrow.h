#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QPainter>

class Item;

class Arrow: public QGraphicsLineItem
{
public:
    enum { Type = UserType +4 };

    Arrow(Item *startItem, Item *endItem, QGraphicsItem *parent = nullptr);

    int type() const override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color);
    Item *startItem() const;
    Item *endItem() const;

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    Item *myStartItem;
    Item *myEndItem;
    QPolygonF arrowHead;
    QColor myColor = Qt::black;
};
#endif // ARROW_H
