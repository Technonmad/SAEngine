#include "Firefighters.h"
#include "qgraphicsscene.h"

#include <QDateTime>

Firefighters::Firefighters(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/firefighter.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);
}

Firefighters::~Firefighters()
{
    delete m_pixmapItem;
}

QRectF Firefighters::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Firefighters::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Firefighters::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Firefighters::type() const
{
    return Type;
}

QVariant Firefighters::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Firefighters::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Firefighters::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Firefighters::receiveMessage(const QString &message)
{
    qDebug() << message << "\n";
//    QDateTime currentTime = QDateTime::currentDateTime();
//    textEdit->append("[ " + currentTime.toString() + " ] " + message);
}
