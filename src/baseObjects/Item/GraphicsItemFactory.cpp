#include "GraphicsItemFactory.h"
#include "ManagerItem.h"
#include "WarehouseItem.h"

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
    case GraphicsItem::Manager:
        return new ManagerItem(contextMenu, parent);
        break;
    default:
        return nullptr;
    }
}
