#ifndef PACKAGING_H
#define PACKAGING_H

#include "Arrow/Arrow.h"
#include <QTextEdit>
#include <QVariant>
#include <Item/GraphicsItem.h>

class Packaging : public GraphicsItem
{
    Q_OBJECT
public:
    Packaging(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    ~Packaging();

//public:
//    QGraphicsPixmapItem *m_pixmapItem;
//    QGraphicsTextItem *m_textItem;

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void addArrow(Arrow *arrow) override;
    int type() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void removeArrow(Arrow *arrow) override;
    void removeArrows() override;

signals:
    void sendMessage(DiagramEventType event, const QString &message);
    void fireEvent();
    void brakeEvent();
    void okEvent();

public slots:
    void receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message) override;
    void wakeUp() override;
    void startEvents();
    void onFireEvent();
    void onBrakeEvent();
    void onOkEvent();

private:
    QTimer *timer;
};

#endif // PACKAGING_H
