#include "Tecnician.h"
#include "qgraphicsscene.h"

#include <QDateTime>

Tecnician::Tecnician(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/tecnician.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);
}

Tecnician::~Tecnician()
{
    delete m_pixmapItem;
}

QRectF Tecnician::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Tecnician::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Tecnician::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Tecnician::type() const
{
    return Type;
}

QVariant Tecnician::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Tecnician::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Tecnician::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Tecnician::receiveMessage(const QString &message)
{
    qDebug() << message << "\n";
//    QDateTime currentTime = QDateTime::currentDateTime();
//    textEdit->append("[ " + currentTime.toString() + " ] " + message);
}
