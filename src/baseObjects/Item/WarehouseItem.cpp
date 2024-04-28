#include "WarehouseItem.h"
#include "qgraphicsscene.h"

WarehouseItem::WarehouseItem(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/warehouse.png");
    m_pixmapItem = new QGraphicsPixmapItem(pixmap);
//    m_textItem = new QGraphicsTextItem("100");

//    m_pixmapItem->setPos(0, 0);
//    m_textItem->setPos(0, m_pixmapItem->pixmap().height());
}

WarehouseItem::~WarehouseItem()
{
    delete m_pixmapItem;
//    delete m_textItem;
}

QRectF WarehouseItem::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void WarehouseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
//    m_textItem->paint(painter, option, widget);
}

void WarehouseItem::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int WarehouseItem::type() const
{
    return Type;
}

QVariant WarehouseItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void WarehouseItem::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void WarehouseItem::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}
