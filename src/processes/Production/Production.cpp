#include "Production.h"
#include "qgraphicsscene.h"

#include <QDateTime>
#include <QTimer>
#include <QRandomGenerator>

Production::Production(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/processes/production.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);

    connect(this, &Production::brakeEvent, this, &Production::onBrakeEvent);
    connect(this, &Production::fireEvent, this, &Production::onFireEvent);
    connect(this, &Production::okEvent, this, &Production::onOkEvent);
}

Production::~Production()
{
    delete m_pixmapItem;
}

QRectF Production::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Production::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Production::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Production::type() const
{
    return Type;
}

QVariant Production::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Production::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Production::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Production::receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message)
{
    if (senderType == DiagramType::Firefighters && event == DiagramEventType::FireOutEvent){
        emit okEvent();
    } else if (senderType == DiagramType::Tecnician && event == DiagramEventType::RepairEvent){
        emit okEvent();
    } else {
        return;
    }
}

void Production::wakeUp()
{
    timer = new QTimer(this);
    timer->setInterval(5000);
    connect(timer, &QTimer::timeout, this, &Production::startEvents);
    timer->start();
}

void Production::startEvents()
{
    int eventNumber = QRandomGenerator::global()->bounded(3) + 1;
    switch (eventNumber) {
    case 1:
        emit brakeEvent();
        timer->stop();
        break;
    case 2:
        emit okEvent();
        break;
    case 3:
        emit fireEvent();
        timer->stop();
        break;
    default:
        break;
    }
}

void Production::onFireEvent()
{
    emit sendMessage(DiagramEventType::FireEvent, "У меня пожар!");
}

void Production::onBrakeEvent()
{
    emit sendMessage(DiagramEventType::BrakeEvent, "Я сломан");
}

void Production::onOkEvent()
{
    emit sendMessage(DiagramEventType::OkEvent, "Произвожу товар");
    timer->start();
}
