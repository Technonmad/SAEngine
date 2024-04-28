#ifndef IGRAPHICSITEMFACTORY_H
#define IGRAPHICSITEMFACTORY_H

#include "GraphicsItem.h"


class IGraphicsItemFactory {
public:
    virtual ~IGraphicsItemFactory() {};
    virtual GraphicsItem* create(GraphicsItem::DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = nullptr) = 0;
};

#endif // IGRAPHICSITEMFACTORY_H
