#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMenu>

class Arrow;

class Item: public QGraphicsItem
{
public:
    enum { Type = UserType + 15 };
    enum DiagramType { Step, Conditional, StartEnd, Io };

    Item( DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = nullptr );

    void removeArrow(Arrow *arrow);
    void removeArrows();
    DiagramType diagramType() const;
    QPolygonF polygon() const;
    void addArrow(Arrow *arrow);
    QPixmap image() const;
    int type() const override;

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    DiagramType myDiagramType;
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Arrow *> arrows;
};

#endif // NODE_H
