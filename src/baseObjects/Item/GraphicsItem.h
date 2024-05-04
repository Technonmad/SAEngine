#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QGraphicsItem>
#include <QMenu>

class Arrow;

class GraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 15 };
    enum DiagramType {
        AICamera,
        FireSensor,
        Firefighters,
        SecurityPost,
        AccessControl,
        Engineers,
        Managers,
        Warehouse,
        ProductionLine,
        PackingLine,
        Delivery,
        Tecnician,
    };

    Q_ENUM(DiagramType)

    GraphicsItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = nullptr);

    virtual ~GraphicsItem(){};

    QRectF boundingRect() const override = 0;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;
    DiagramType diagramType() const;
    virtual void addArrow(Arrow *arrow) = 0;
    virtual int type() const override = 0;
    virtual void removeArrow(Arrow *arrow) = 0;
    virtual void removeArrows() = 0;
signals:
    void sendMessage(const QString &message);
public slots:
    virtual void receiveMessage(const QString &message) = 0;

protected:
//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QGraphicsPixmapItem *m_pixmapItem;
//    QGraphicsTextItem *m_textItem;
    QList<Arrow *> arrows;

private:
    DiagramType myDiagramType;
    QMenu *myContextMenu;
};

#endif // GRAPHICSITEM_H
