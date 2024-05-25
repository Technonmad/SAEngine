#include "WarehouseItem.h"
#include "qgraphicsscene.h"

#include <QDateTime>
#include <QTimer>
#include <QRandomGenerator>

WarehouseItem::WarehouseItem(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Warehouse, contextMenu, parent)
{
    QPixmap pixmap(":/images/processes/warehouse.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);

    connect(this, &WarehouseItem::fireEvent, this, &WarehouseItem::onFireEvent);
    connect(this, &WarehouseItem::startProcessEvent, this, &WarehouseItem::onStartProcessEvent);
    connect(this, &WarehouseItem::endProcessEvent, this, &WarehouseItem::onEndProcessEvent);
    connect(this, &WarehouseItem::continueProcessEvent, this, &WarehouseItem::onContinueProcessEvent);
    connect(this, &WarehouseItem::startDeliveringEvent, this, &WarehouseItem::onStartDeliveringEvent);
    connect(this, &WarehouseItem::continueDeliveringEvent, this, &WarehouseItem::onContinueDeliveringEvent);
    connect(this, &WarehouseItem::endDeliveringEvent, this, &WarehouseItem::onEndDeliveringEvent);
}

WarehouseItem::~WarehouseItem()
{
    delete m_pixmapItem;
}

QRectF WarehouseItem::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void WarehouseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void WarehouseItem::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int WarehouseItem::type() const
{
    return Type;
}

QVariant WarehouseItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void WarehouseItem::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void WarehouseItem::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void WarehouseItem::receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message)
{
    if (state != DiagramAgentState::Stopped){
        if (senderType == DiagramType::ProductionLine && event == DiagramEventType::ProcessEndEvent){
            emit startProcessEvent();
        } else if (senderType == DiagramType::Managers && event == DiagramEventType::ProcessEndEvent){
            emit startDeliveringEvent();
        } else if (senderType == DiagramType::Firefighters && event == DiagramEventType::FireOutEvent){
            if (state == DiagramAgentState::Working)
                emit continueProcessEvent();
            else if (state == DiagramAgentState::SendingToDeliver)
                emit continueDeliveringEvent();
        } else {
            return;
        }
    }
}

void WarehouseItem::wakeUp()
{
    emit sendMessage(diagramType(), DiagramEventType::StartEvent, "Начинаю работу");
    processTimer = new QTimer(this);
    processTimer->setInterval(3000);
    connect(processTimer, &QTimer::timeout, this, &WarehouseItem::onEndProcessEvent);

    eventTimer = new QTimer(this);
    eventTimer->setInterval(5000);
    connect(eventTimer, &QTimer::timeout, this, &WarehouseItem::startEvents);
    eventTimer->start();

    processTimer = new QTimer(this);
    processTimer->setInterval(5000);
    connect(processTimer, &QTimer::timeout, this, &WarehouseItem::onEndDeliveringEvent);

    state = DiagramAgentState::Working;
}

void WarehouseItem::pauseAgents()
{
    oldProcessState = processTimer->isActive();
    oldEventState = eventTimer->isActive();
    processTimer->stop();
    eventTimer->stop();
}

void WarehouseItem::continueAgents()
{
    if (oldProcessState)
        processTimer->start();

    if (oldEventState)
        eventTimer->start();
}

void WarehouseItem::startEvents()
{
    int eventNumber = QRandomGenerator::global()->bounded(9) + 1;
    switch (eventNumber) {
    case 3:
        emit fireEvent();
        break;
    default:
        break;
    }
}

void WarehouseItem::onFireEvent()
{
    eventTimer->stop();
    processTimer->stop();
    state = DiagramAgentState::Stopped;
    emit sendMessage(diagramType(), DiagramEventType::FireEvent, "У меня пожар!");
}

void WarehouseItem::onStartProcessEvent()
{
    emit sendMessage(diagramType(), DiagramEventType::ProcessStartEvent, "Раскладываю товар...");
    eventTimer->start();
    state = DiagramAgentState::Working;

    processTimer->start();
}

void WarehouseItem::onEndProcessEvent()
{
    state = DiagramAgentState::Working;
    emit sendMessage(diagramType(), DiagramEventType::ProcessEndEvent, "Товар разложен");
}

void WarehouseItem::onContinueProcessEvent()
{
    eventTimer->start();
    processTimer->start();
    state = DiagramAgentState::Working;
    emit sendMessage(diagramType(), DiagramEventType::ProcessEndEvent, "Продолжаю раскладывать товар...");
}

void WarehouseItem::onStartDeliveringEvent()
{
    emit sendMessage(diagramType(), DiagramEventType::StartDeliveryEvent, "Отправляю товар в доставку...");
    eventTimer->start();
    state = DiagramAgentState::Working;

    processTimer->start();
}

void WarehouseItem::onContinueDeliveringEvent()
{
    eventTimer->start();
    processTimer->start();
    state = DiagramAgentState::Working;
    emit sendMessage(diagramType(), DiagramEventType::ContinueDeliveryEvent, "Продолжаю раскладывать товар...");
}

void WarehouseItem::onEndDeliveringEvent()
{
    state = DiagramAgentState::Working;
    emit sendMessage(diagramType(), DiagramEventType::EndDeliveryEvent, "Товар отправлен в доставку");
}

