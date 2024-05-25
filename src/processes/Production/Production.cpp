#include "Production.h"
#include "qgraphicsscene.h"

#include <QDateTime>
#include <QTimer>
#include <QRandomGenerator>

Production::Production(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::ProductionLine, contextMenu, parent)
{
    QPixmap pixmap(":/images/processes/production.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);

    connect(this, &Production::brakeEvent, this, &Production::onBrakeEvent);
    connect(this, &Production::fireEvent, this, &Production::onFireEvent);
    connect(this, &Production::startProcessEvent, this, &Production::onStartProcessEvent);
    connect(this, &Production::endProcessEvent, this, &Production::onEndProcessEvent);
    connect(this, &Production::continueProcessEvent, this, &Production::onContinueProcessEvent);
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
        emit continueProcessEvent();
    } else if (senderType == DiagramType::Tecnician && event == DiagramEventType::RepairEvent){
        emit continueProcessEvent();
    } else {
        return;
    }
}

void Production::wakeUp()
{
    emit sendMessage(diagramType(), DiagramEventType::StartEvent, "Начинаю работу");
    eventTimer = new QTimer(this);
    eventTimer->setInterval(5000);
    connect(eventTimer, &QTimer::timeout, this, &Production::startEvents);

    processTimer = new QTimer(this);
    processTimer->setInterval(10000);
    connect(processTimer, &QTimer::timeout, this, &Production::onEndProcessEvent);
    eventTimer->start();

    state = DiagramAgentState::Working;
    emit startProcessEvent();
}

void Production::pauseAgents()
{
    oldProcessState = processTimer->isActive();
    oldEventState = eventTimer->isActive();
    processTimer->stop();
    eventTimer->stop();
}

void Production::continueAgents()
{
    if (oldProcessState)
        processTimer->start();

    if (oldEventState)
        eventTimer->start();
}

void Production::startEvents()
{
    int eventNumber = QRandomGenerator::global()->bounded(9) + 1;
    switch (eventNumber) {
    case 1:
        emit brakeEvent();
        break;
    case 3:
        emit fireEvent();
        break;
    default:
        break;
    }
}

void Production::onFireEvent()
{
    eventTimer->stop();
    processTimer->stop();
    state = DiagramAgentState::Stopped;
    emit sendMessage(diagramType(), DiagramEventType::FireEvent, "У меня пожар!");
}

void Production::onBrakeEvent()
{
    eventTimer->stop();
    processTimer->stop();
    state = DiagramAgentState::Stopped;
    emit sendMessage(diagramType(), DiagramEventType::BrakeEvent, "Я сломан");
}

void Production::onStartProcessEvent()
{
    emit sendMessage(diagramType(), DiagramEventType::ProcessStartEvent, "Произвожу товар...");
    eventTimer->start();
    processTimer->start();
}

void Production::onEndProcessEvent()
{
    emit sendMessage(diagramType(), DiagramEventType::ProcessEndEvent, "Товар произведен. Отправляю на склад...");
}

void Production::onContinueProcessEvent()
{
    eventTimer->start();
    processTimer->start();
    state = DiagramAgentState::Working;
    emit sendMessage(diagramType(), DiagramEventType::ProcessContinueEvent, "Продолжаю производство...");
}
