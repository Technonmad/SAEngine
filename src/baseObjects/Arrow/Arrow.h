#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QPen>
#include <QPainter>

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
    void sendMessageToStartObject(const QString &message);
    void sendMessageToEndObject(const QString &message);

public slots:
    void handleMessage(const QString &message);

private:
    GraphicsItem *myStartItem;
    GraphicsItem *myEndItem;
    QPolygonF arrowHead;
    QColor myColor = Qt::black;
};
#endif // ARROW_H
