#ifndef TECNICIAN_H
#define TECNICIAN_H

#include "Arrow/Arrow.h"
#include <QTextEdit>
#include <QVariant>
#include <Item/GraphicsItem.h>

class Tecnician : public GraphicsItem
{
    Q_OBJECT
public:
    Tecnician(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    ~Tecnician();

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
    void sendMessage(const QString &message);

public slots:
    void receiveMessage(const QString &message) override;
private:
//    QList<Arrow *> arrows;
};

#endif // TECNICIAN_H
