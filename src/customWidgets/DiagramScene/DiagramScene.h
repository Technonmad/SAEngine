#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <Item/IGraphicsItemFactory.h>
#include "Item/GraphicsItem.h"
#include "qmetaobject.h"

class DiagramScene: public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, MoveItem };

    explicit DiagramScene(QMenu *itemMenu, QObject *parent = nullptr);
    QColor lineColor() const;
    void setLineColor(const QColor &color);

public slots:
    void setMode(Mode mode);
    void setItemType(GraphicsItem::DiagramType type);
    void itemMessageHandle(GraphicsItem::DiagramEventType event, const QString &message);
    void startAgents();

signals:
    void itemInserted(GraphicsItem *item);
    void itemSelected(QGraphicsItem *item);
    void messageSent(const QString &message);
    void wakeUpAgents();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    bool isItemChange(int type) const;

    GraphicsItem::DiagramType myItemType;
    QMenu *myItemMenu;
    QGraphicsLineItem *line;
    GraphicsItem *item;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QColor myLineColor;
    std::unique_ptr<IGraphicsItemFactory> itemFactory;
};
#endif // DIAGRAMSCENE_H
