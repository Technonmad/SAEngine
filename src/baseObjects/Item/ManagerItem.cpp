#include "ManagerItem.h"

ManagerItem::ManagerItem(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Manager, contextMenu, parent)
{

}

QRectF ManagerItem::boundingRect() const
{
    return {};
}

void ManagerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
