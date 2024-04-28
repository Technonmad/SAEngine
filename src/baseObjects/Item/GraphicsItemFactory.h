#ifndef GRAPHICSITEMFACTORY_H
#define GRAPHICSITEMFACTORY_H

#include "IGraphicsItemFactory.h"

class GraphicsItemFactory : public IGraphicsItemFactory
{
public:
    GraphicsItemFactory();
    ~GraphicsItemFactory();

    GraphicsItem *create(GraphicsItem::DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent) override;
};

#endif // GRAPHICSITEMFACTORY_H
