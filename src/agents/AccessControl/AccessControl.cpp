#include "AccessControl.h"
#include "qgraphicsscene.h"

#include <QDateTime>

AccessControl::AccessControl(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/accessControl.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);
}

AccessControl::~AccessControl()
{
    delete m_pixmapItem;
}

QRectF AccessControl::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void AccessControl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void AccessControl::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int AccessControl::type() const
{
    return Type;
}

QVariant AccessControl::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void AccessControl::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void AccessControl::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void AccessControl::receiveMessage(const QString &message)
{
    qDebug() << message << "\n";
}
