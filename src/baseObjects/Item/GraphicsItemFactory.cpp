#include "GraphicsItemFactory.h"
#include <Storing/WarehouseItem.h>
#include <Firefighters/Firefighters.h>
#include <FireSensor/FireSensor.h>
#include <Managers/Managers.h>
#include <Tecnician/Tecnician.h>
#include <Delivery/Delivery.h>
#include <Production/Production.h>

GraphicsItemFactory::GraphicsItemFactory()
{

}

GraphicsItemFactory::~GraphicsItemFactory()
{

}

GraphicsItem *GraphicsItemFactory::create(GraphicsItem::DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent)
{
    switch (diagramType) {
    case GraphicsItem::Firefighters:
        return new Firefighters(contextMenu, parent);
        break;
    case GraphicsItem::FireSensor:
        return new Firesensor(contextMenu, parent);
        break;
    case GraphicsItem::Managers:
        return new Managers(contextMenu, parent);
        break;
    case GraphicsItem::Tecnician:
        return new Tecnician(contextMenu, parent);
        break;
    case GraphicsItem::Delivery:
        return new Delivery(contextMenu, parent);
        break;
    case GraphicsItem::ProductionLine:
        return new Production(contextMenu, parent);
        break;
    case GraphicsItem::Warehouse:
        return new WarehouseItem(contextMenu, parent);
        break;
    default:
        return nullptr;
    }
}
