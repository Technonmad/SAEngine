#ifndef MANAGERITEM_H
#define MANAGERITEM_H

#include "GraphicsItem.h"

class ManagerItem : public GraphicsItem
{
public:
    ManagerItem(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

public:
    QGraphicsPixmapItem *m_pixmapItem;
    QGraphicsTextItem *m_textItem;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // MANAGERITEM_H
