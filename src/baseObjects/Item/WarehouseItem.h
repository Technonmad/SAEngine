#ifndef WAREHOUSEITEM_H
#define WAREHOUSEITEM_H

#include "GraphicsItem.h"

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
};

#endif // WAREHOUSEITEM_H
