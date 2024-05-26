#include "Firefighters.h"
#include "qgraphicsscene.h"

#include <QDateTime>
#include <QTimer>

Firefighters::Firefighters(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Firefighters, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/firefighter.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);

    connect(this, &Firefighters::startProcessEvent, this, &Firefighters::onStartProcessEvent);
}

Firefighters::~Firefighters()
{
    delete m_pixmapItem;
}

QRectF Firefighters::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Firefighters::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Firefighters::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Firefighters::type() const
{
    return Type;
}

QVariant Firefighters::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Firefighters::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Firefighters::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Firefighters::receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message)
{
    if (senderType == DiagramType::FireSensor && event == DiagramEventType::FireEvent){
        emit startProcessEvent();
    } else {
        return;
    }
}

void Firefighters::wakeUp()
{
    emit sendMessage(diagramType(), DiagramEventType::StartEvent, "Начинаю работу");
    processTimer = new QTimer(this);
    processTimer->setInterval(7000);

    state = DiagramAgentState::Stopped;
}

void Firefighters::pauseAgents()
{
    oldProcessState = processTimer->isActive();
    processTimer->stop();
}

void Firefighters::continueAgents()
{
    if (oldProcessState)
        processTimer->start();
}

void Firefighters::onStartProcessEvent()
{
    emit sendMessage(diagramType(), DiagramEventType::ProcessStartEvent, "Тушим пожар...");
    state = DiagramAgentState::Working;

    connect(processTimer, &QTimer::timeout, this, &Firefighters::onEndProcessEvent);
    processTimer->start();
}

void Firefighters::onEndProcessEvent()
{
    emit sendMessage(diagramType(), DiagramEventType::FireOutEvent, "Пожар потушен");
    processTimer->stop();
}
