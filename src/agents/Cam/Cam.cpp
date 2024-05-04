#include "Cam.h"
#include "qgraphicsscene.h"

#include <QDateTime>

Cam::Cam(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/cam.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);
}

Cam::~Cam()
{
    delete m_pixmapItem;
}

QRectF Cam::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Cam::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Cam::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Cam::type() const
{
    return Type;
}

QVariant Cam::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Cam::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Cam::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Cam::receiveMessage(const QString &message)
{
    qDebug() << message << "\n";
//    QDateTime currentTime = QDateTime::currentDateTime();
//    textEdit->append("[ " + currentTime.toString() + " ] " + message);
}
