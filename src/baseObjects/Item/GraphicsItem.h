#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QGraphicsItem>
#include <QMenu>

class Arrow;

class GraphicsItem : public QGraphicsItem
{
public:
    enum { Type = UserType + 15 };
    enum DiagramType {
        Warehouse,
        Manager,
        ProductionLine,
        MonitoringSystem,
        PackingLine,
        CarTransfer,
        Customer
    };

    GraphicsItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    virtual ~GraphicsItem(){};

    QRectF boundingRect() const override = 0;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

protected:
//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
//    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    QGraphicsPixmapItem *m_pixmapItem;
    QGraphicsTextItem *m_textItem;

private:
    DiagramType myDiagramType;
    QMenu *myContextMenu;
};

#endif // GRAPHICSITEM_H
