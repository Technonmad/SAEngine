#include "Security.h"
#include "qgraphicsscene.h"

#include <QDateTime>

Security::Security(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/security.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);
}

Security::~Security()
{
    delete m_pixmapItem;
}

QRectF Security::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Security::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Security::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Security::type() const
{
    return Type;
}

QVariant Security::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Security::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Security::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Security::receiveMessage(const QString &message)
{
    qDebug() << message << "\n";
//    QDateTime currentTime = QDateTime::currentDateTime();
//    textEdit->append("[ " + currentTime.toString() + " ] " + message);
}
