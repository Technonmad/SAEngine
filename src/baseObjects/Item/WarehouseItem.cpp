#include "WarehouseItem.h"

WarehouseItem::WarehouseItem(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/warehouse.png");
    m_pixmapItem = new QGraphicsPixmapItem(pixmap);
    m_textItem = new QGraphicsTextItem("100");

    m_pixmapItem->setPos(0, 0);
    m_textItem->setPos(0, m_pixmapItem->pixmap().height());
}

WarehouseItem::~WarehouseItem()
{
    delete m_pixmapItem;
    delete m_textItem;
}

QRectF WarehouseItem::boundingRect() const
{
    return m_pixmapItem->boundingRect().united(m_textItem->boundingRect());
}

void WarehouseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
    m_textItem->paint(painter, option, widget);
}
