#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "Arrow/Arrow.h"
#include <QTextEdit>
#include <QVariant>
#include <Item/GraphicsItem.h>

class Production : public GraphicsItem
{
    Q_OBJECT
public:
    Production(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    ~Production();

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

#endif // PRODUCTION_H
