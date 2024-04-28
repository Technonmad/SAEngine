#ifndef WAREHOUSEITEM_H
#define WAREHOUSEITEM_H

#include "GraphicsItem.h"
#include "Arrow/Arrow.h"
#include <QVariant>

class WarehouseItem : public GraphicsItem
{
public:
    WarehouseItem(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    ~WarehouseItem();

//public:
//    QGraphicsPixmapItem *m_pixmapItem;
//    QGraphicsTextItem *m_textItem;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void addArrow(Arrow *arrow) override;
    int type() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void removeArrow(Arrow *arrow) override;
    void removeArrows() override;

private:
//    QList<Arrow *> arrows;
};

#endif // WAREHOUSEITEM_H
