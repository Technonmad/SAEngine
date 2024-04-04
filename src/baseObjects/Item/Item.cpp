#include "Item.h"
#include "Arrow/Arrow.h"
#include "qgraphicssceneevent.h"

Item::Item(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      myDiagramType(diagramType),
      myContextMenu(contextMenu)
{
    //TODO: сделать switch для типов Items
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void Item::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Item::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

Item::DiagramType Item::diagramType() const
{
    return myDiagramType;
}

QPolygonF Item::polygon() const
{
    return myPolygon;
}

QPixmap Item::image() const
{

}

void Item::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->popup(event->screenPos());
}

QVariant Item::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow : std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}
