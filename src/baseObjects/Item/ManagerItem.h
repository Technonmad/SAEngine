#ifndef MANAGERITEM_H
#define MANAGERITEM_H

#include "GraphicsItem.h"
#include "Arrow/Arrow.h"

#include <QVariant>

class ManagerItem : public GraphicsItem
{
    Q_OBJECT
public:
    ManagerItem(QMenu *contextMenu, QGraphicsItem *parent = nullptr);

public:
    QGraphicsPixmapItem *m_pixmapItem;
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

protected:
    QList<Arrow *> arrows;
};

#endif // MANAGERITEM_H
