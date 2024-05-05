#include "Packaging.h"
#include "qgraphicsscene.h"

#include <QDateTime>
#include <QTimer>
#include <QRandomGenerator>

Packaging::Packaging(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/processes/packaging.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);

    connect(this, &Packaging::brakeEvent, this, &Packaging::onBrakeEvent);
    connect(this, &Packaging::fireEvent, this, &Packaging::onFireEvent);
    connect(this, &Packaging::okEvent, this, &Packaging::onOkEvent);
}

Packaging::~Packaging()
{
    delete m_pixmapItem;
}

QRectF Packaging::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Packaging::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Packaging::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Packaging::type() const
{
    return Type;
}

QVariant Packaging::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Packaging::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Packaging::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Packaging::receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message)
{
    if (senderType == DiagramType::Firefighters && event == DiagramEventType::FireOutEvent){
        emit okEvent();
    } else if (senderType == DiagramType::Tecnician && event == DiagramEventType::RepairEvent){
        emit okEvent();
    } else if (senderType == DiagramType::ProductionLine
        && event == DiagramEventType::OkEvent){
        emit okEvent();
    } else {
        return;
    }
}

void Packaging::wakeUp()
{
    timer = new QTimer(this);
    timer->setInterval(5000);
    connect(timer, &QTimer::timeout, this, &Packaging::startEvents);
    timer->start();
}

void Packaging::startEvents()
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
        break;
    default:
        break;
    }
}

void Packaging::onFireEvent()
{
    emit sendMessage(DiagramEventType::FireEvent, "У меня пожар!");
}

void Packaging::onBrakeEvent()
{
    emit sendMessage(DiagramEventType::BrakeEvent, "Я сломан");
}

void Packaging::onOkEvent()
{
    emit sendMessage(DiagramEventType::OkEvent, "Упаковываю товар");
    timer->start();
}
