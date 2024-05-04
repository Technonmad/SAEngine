#include "WarehouseItem.h"
#include "qgraphicsscene.h"

#include <QDateTime>

WarehouseItem::WarehouseItem(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/processes/warehouse.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);
}

WarehouseItem::~WarehouseItem()
{
    delete m_pixmapItem;
}

QRectF WarehouseItem::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void WarehouseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
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

void WarehouseItem::receiveMessage(const QString &message)
{
    qDebug() << message << "\n";
//    QDateTime currentTime = QDateTime::currentDateTime();
//    textEdit->append("[ " + currentTime.toString() + " ] " + message);
}
