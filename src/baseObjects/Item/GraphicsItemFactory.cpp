#include "GraphicsItemFactory.h"
#include <Storing/WarehouseItem.h>
#include <AccessControl/AccessControl.h>
#include <Cam/Cam.h>
#include <Engineers/Engineers.h>
#include <Firefighters/Firefighters.h>
#include <FireSensor/FireSensor.h>
#include <Managers/Managers.h>
#include <Security/Security.h>
#include <Tecnician/Tecnician.h>
#include <Delivery/Delivery.h>
#include <Packaging/Packaging.h>
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
    case GraphicsItem::AccessControl:
        return new AccessControl(contextMenu, parent);
        break;
    case GraphicsItem::AICamera:
        return new Cam(contextMenu, parent);
        break;
    case GraphicsItem::Engineers:
        return new Engineers(contextMenu, parent);
        break;
    case GraphicsItem::Firefighters:
        return new Firefighters(contextMenu, parent);
        break;
    case GraphicsItem::FireSensor:
        return new Firesensor(contextMenu, parent);
        break;
    case GraphicsItem::Managers:
        return new Managers(contextMenu, parent);
        break;
    case GraphicsItem::SecurityPost:
        return new Security(contextMenu, parent);
        break;
    case GraphicsItem::Tecnician:
        return new Tecnician(contextMenu, parent);
        break;
    case GraphicsItem::Delivery:
        return new Delivery(contextMenu, parent);
        break;
    case GraphicsItem::PackingLine:
        return new Packaging(contextMenu, parent);
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
