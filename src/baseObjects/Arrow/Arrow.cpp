#include "Arrow.h"
#include "Item/GraphicsItem.h"
#include <QGraphicsLineItem>

Arrow::Arrow(GraphicsItem *startItem, GraphicsItem *endItem, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), myStartItem(startItem), myEndItem(endItem)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QObject::connect(startItem, &GraphicsItem::sendMessage, this, &Arrow::handleMessage);
    QObject::connect(endItem, &GraphicsItem::sendMessage, this, &Arrow::handleMessage);
    QObject::connect(this, &Arrow::sendMessageToStartObject, startItem, &GraphicsItem::receiveMessage);
    QObject::connect(this, &Arrow::sendMessageToEndObject, endItem, &GraphicsItem::receiveMessage);
}

int Arrow::type() const
{
    return Type;
}

//QRectF Arrow::boundingRect() const
//{
//    qreal extra = (pen().width() + 20) / 2.0;

//    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
//                                      line().p2().y() - line().p2().y()))
//            .normalized()
//            .adjusted(-extra, -extra, extra, extra);
//}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Arrow::setColor(const QColor &color)
{
    myColor = color;
}

GraphicsItem *Arrow::startItem() const
{
    return myStartItem;
}

GraphicsItem *Arrow::endItem() const
{
    return myEndItem;
}

void Arrow::updatePosition()
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (myStartItem->collidesWithItem(myEndItem))
        return;

    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(myColor);

    QPointF startItemCenter = myStartItem->boundingRect().center();
    QPointF endItemPoint = myEndItem->boundingRect().center();

    QPointF arrowEndPoint = mapFromItem(myEndItem, endItemPoint);
    QPointF arrowStartPoint = mapFromItem(myStartItem, startItemCenter);

    setLine(QLineF(arrowStartPoint, arrowEndPoint));

    double angle = std::atan2(-line().dy(), line().dx());

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                    cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                    cos(angle + M_PI - M_PI / 3) * arrowSize);
    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
    painter->drawLine(line());
    painter->drawLine(arrowStartPoint, arrowEndPoint);
    painter->drawPolygon(arrowHead);
    if (isSelected()) {
        painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }


}

void Arrow::handleMessage(const QString &message)
{
    emit sendMessageToEndObject(message);
}
