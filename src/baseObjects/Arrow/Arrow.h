#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QPainter>

#include <Item/GraphicsItem.h>

class GraphicsItem;

class Arrow: public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    enum { Type = UserType +4 };

    Arrow(GraphicsItem *startItem, GraphicsItem *endItem, QGraphicsItem *parent = nullptr);

    int type() const override;
//    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color);
    GraphicsItem *startItem() const;
    GraphicsItem *endItem() const;

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

signals:
    void receivedMessage(const QString &message);
    void sendMessageToStartObject(GraphicsItem::DiagramType type, GraphicsItem::DiagramEventType event,
                                  const QString &message);
    void sendMessageToEndObject(GraphicsItem::DiagramType type, GraphicsItem::DiagramEventType event,
                                const QString &message);

public slots:
    void handleMessageFromStartObject(GraphicsItem::DiagramType type, GraphicsItem::DiagramEventType event,
                                      const QString &message);
    void handleMessageFromEndObject(GraphicsItem::DiagramType type, GraphicsItem::DiagramEventType event,
                                    const QString &message);

private:
    GraphicsItem *myStartItem;
    GraphicsItem *myEndItem;
    QPolygonF arrowHead;
    QColor myColor = Qt::red;
};
#endif // ARROW_H
