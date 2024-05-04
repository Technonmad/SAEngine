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

void ManagerItem::addArrow(Arrow *arrow)
{

}

int ManagerItem::type() const
{
    return Type;
}

QVariant ManagerItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    return value;
}

void ManagerItem::removeArrow(Arrow *arrow)
{

}

void ManagerItem::removeArrows()
{

}

void ManagerItem::receiveMessage(const QString &message)
{

}
