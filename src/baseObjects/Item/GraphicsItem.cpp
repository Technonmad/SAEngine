#include "GraphicsItem.h"
#include <QGraphicsSceneContextMenuEvent>

GraphicsItem::GraphicsItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsItem(parent), myDiagramType(diagramType), myContextMenu(contextMenu)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

GraphicsItem::DiagramType GraphicsItem::diagramType() const
{
    return myDiagramType;
}
