#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include "Item/Item.h"

class DiagramScene: public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, /*InsertText, */MoveItem };

    explicit DiagramScene(QMenu *itemMenu, QObject *parent = nullptr);
    QColor lineColor() const;
    void setLineColor(const QColor &color);

public slots:
    void setMode(Mode mode);
    void setItemType(Item::DiagramType type);
//    void editorLostFocus(TextItem *item);

signals:
    void itemInserted(Item *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    bool isItemChange(int type) const;

    Item::DiagramType myItemType;
    QMenu *myItemMenu;
    QGraphicsLineItem *line;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QColor myLineColor;
};
#endif // DIAGRAMSCENE_H