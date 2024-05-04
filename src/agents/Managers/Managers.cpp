#include "Managers.h"
#include "qgraphicsscene.h"

#include <QDateTime>

Managers::Managers(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/managers.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);
}

Managers::~Managers()
{
    delete m_pixmapItem;
}

QRectF Managers::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Managers::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Managers::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Managers::type() const
{
    return Type;
}

QVariant Managers::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Managers::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Managers::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Managers::receiveMessage(const QString &message)
{
    qDebug() << message << "\n";
//    QDateTime currentTime = QDateTime::currentDateTime();
//    textEdit->append("[ " + currentTime.toString() + " ] " + message);
}
