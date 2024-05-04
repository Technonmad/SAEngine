#include "DiagramScene.h"
#include <QTextCursor>
#include "Arrow/Arrow.h"
#include "Item/GraphicsItemFactory.h"

DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent), itemFactory(std::make_unique<GraphicsItemFactory>(GraphicsItemFactory()))
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = GraphicsItem::Warehouse;
    line = nullptr;
    myLineColor = Qt::black;
}

QColor DiagramScene::lineColor() const
{
    return myLineColor;
}

void DiagramScene::setLineColor(const QColor &color)
{
    myLineColor = color;
    if (isItemChange(Arrow::Type)) {
        Arrow *item = qgraphicsitem_cast<Arrow *>(selectedItems().first());
        item->setColor(myLineColor);
        update();
    }
}

void DiagramScene::setMode(Mode mode)
{
    myMode = mode;
}

void DiagramScene::setItemType(GraphicsItem::DiagramType type/*Item::DiagramType type*/)
{
    myItemType = type;
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

//    Item *item;
    GraphicsItem *item;
    switch (myMode) {
        case InsertItem:
//            item = new Item(myItemType, myItemMenu);
            item = itemFactory.get()->create(myItemType, myItemMenu);
            addItem(item);
            item->setPos(mouseEvent->scenePos());
            emit itemInserted(item);
            break;
        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                                mouseEvent->scenePos()));
            line->setPen(QPen(myLineColor, 2));
            addItem(line);
            break;
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != nullptr) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }
    else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != nullptr && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        if ( startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == GraphicsItem::Type &&
            endItems.first()->type() == GraphicsItem::Type &&
            startItems.first() != endItems.first() )
        {
            GraphicsItem *startItem = qgraphicsitem_cast<GraphicsItem *>(startItems.first());
            GraphicsItem *endItem = qgraphicsitem_cast<GraphicsItem *>(endItems.first());
            Arrow *arrow = new Arrow(startItem, endItem);
            arrow->setColor(myLineColor);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
            emit startItem->sendMessage("Я работаю!");
        }
    }
    line = nullptr;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::isItemChange(int type) const
{
    const QList<QGraphicsItem *> items = selectedItems();
    const auto cb = [type](const QGraphicsItem *item) { return item->type() == type; };
    return std::find_if(items.begin(), items.end(), cb) != items.end();
}
