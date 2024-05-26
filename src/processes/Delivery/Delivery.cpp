#include "Delivery.h"
#include "qgraphicsscene.h"

#include <QDateTime>
#include <QRandomGenerator>
#include <QTimer>

Delivery::Delivery(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Delivery, contextMenu, parent)
{
    QPixmap pixmap(":/images/processes/delivery.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);

    connect(this, &Delivery::deliveryIsHere, this, &Delivery::onDeliveryIsHere);
    connect(this, &Delivery::startProcessEvent, this, &Delivery::onStartProcessEvent);
    connect(this, &Delivery::stopReceiving, this, &Delivery::onStopReceiving);
    connect(this, &Delivery::continueReceiving, this, &Delivery::onContinueReceiving);
    connect(this, &Delivery::goodsReceivedEvent, this, &Delivery::onGoodsReceivedEndEvent);
}

Delivery::~Delivery()
{
    delete m_pixmapItem;
}

QRectF Delivery::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Delivery::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Delivery::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Delivery::type() const
{
    return Type;
}

QVariant Delivery::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Delivery::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Delivery::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Delivery::receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message)
{
    if (state == DiagramAgentState::Working){
        if (senderType == DiagramType::Warehouse && event == DiagramEventType::StartDeliveryEvent){
            emit startProcessEvent();
        } else if (senderType == DiagramType::Warehouse && event == DiagramEventType::FireEvent){
            emit stopReceiving();
        } else if (senderType == DiagramType::Warehouse && event == DiagramEventType::ContinueDeliveryEvent){
            emit continueReceiving();
        } else {
            return;
        }
    } else {
        return;
    }
}

void Delivery::wakeUp()
{
    emit sendMessage(diagramType(), DiagramEventType::StartEvent, "Начинаю работу");
    eventTimer = new QTimer(this);
    eventTimer->setInterval(12000);
    connect(eventTimer, &QTimer::timeout, this, &Delivery::startEvents);
    eventTimer->start();

    processTimer = new QTimer(this);
    processTimer->setInterval(5000);
    connect(processTimer, &QTimer::timeout, this, &Delivery::onGoodsReceivedEndEvent);

    state = DiagramAgentState::Stopped;
}

void Delivery::pauseAgents()
{
    oldProcessState = processTimer->isActive();
    oldEventState = eventTimer->isActive();
    processTimer->stop();
    eventTimer->stop();
}

void Delivery::continueAgents()
{
    if (oldProcessState)
        processTimer->start();

    if (oldEventState)
        eventTimer->start();
}

void Delivery::onStartProcessEvent()
{
    processTimer->start();
    emit sendMessage(diagramType(), DiagramEventType::ProcessStartEvent, "Идет загрузка товара...");
    state = DiagramAgentState::Working;
}

void Delivery::onGoodsReceivedEndEvent()
{
    emit sendMessage(diagramType(), DiagramEventType::DeliveryIsOutEvent, "Товар загружен и доставляется");
    processTimer->stop();
    state = DiagramAgentState::Stopped;
}

void Delivery::startEvents()
{
    int eventNumber = QRandomGenerator::global()->bounded(5) + 1;
    switch (eventNumber) {
    case 1:
        emit deliveryIsHere();
    default:
        break;
    }
}

void Delivery::onStopReceiving()
{
    state = DiagramAgentState::Stopped;
    processTimer->stop();
    emit sendMessage(diagramType(), DiagramEventType::DeliveryIsWaiting, "Погрузка приостановлена...");
}

void Delivery::onContinueReceiving()
{
    state = DiagramAgentState::Working;
    processTimer->start();
    emit sendMessage(diagramType(), DiagramEventType::ContinueDeliveryEvent, "Погрузка продолжается...");
}

void Delivery::onDeliveryIsHere()
{
    emit sendMessage(diagramType(), DiagramEventType::DeliveryIsHereEvent, "Приехала машина...");
    eventTimer->stop();
    state = DiagramAgentState::Working;
}
