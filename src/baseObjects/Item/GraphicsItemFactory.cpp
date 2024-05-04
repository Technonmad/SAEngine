#include "GraphicsItemFactory.h"
#include <Storing/WarehouseItem.h>

GraphicsItemFactory::GraphicsItemFactory()
{

}

GraphicsItemFactory::~GraphicsItemFactory()
{

}

GraphicsItem *GraphicsItemFactory::create(GraphicsItem::DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent)
{
    switch (diagramType) {
    case GraphicsItem::Warehouse:
        return new WarehouseItem(contextMenu, parent);
        break;
    default:
        return nullptr;
    }
}
