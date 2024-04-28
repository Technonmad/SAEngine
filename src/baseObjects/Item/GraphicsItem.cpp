#include "GraphicsItem.h"
//#include "Arrow/Arrow.h"
#include <QGraphicsSceneContextMenuEvent>

GraphicsItem::GraphicsItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent)
    : QGraphicsItem(parent), myDiagramType(diagramType), myContextMenu(contextMenu)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

//void GraphicsItem::addArrow(Arrow *arrow)
//{
//    arrows.append(arrow);
//}

//QRectF GraphicsItem::boundingRect() const
//{
//    return m_pixmapItem->boundingRect().united(m_textItem->boundingRect());
//}

//void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    m_pixmapItem->paint(painter, option, widget);
//    m_textItem->paint(painter, option, widget);
//}

//void GraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
//{
//	scene()->clearSelection();
//    setSelected(true);
//    myContextMenu->exec(event->scenePos());
//}

//QVariant GraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
//{
//    if (change == QGraphicsItem::ItemPositionChange) {
//        for (Arrow *arrow : std::as_const(arrows))
//            arrow->updatePosition();
//    }

//    return value;
//}
