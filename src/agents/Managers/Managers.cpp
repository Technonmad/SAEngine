#include "Managers.h"
#include "qgraphicsscene.h"

#include <QDateTime>
#include <QTimer>

Managers::Managers(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Managers, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/managers.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);

    connect(this, &Managers::startProcessEvent, this, &Managers::onStartProcessEvent);
}

Managers::~Managers()
{
    delete m_pixmapItem;
}

QRectF Managers::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Managers::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Managers::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Managers::type() const
{
    return Type;
}

QVariant Managers::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Managers::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Managers::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Managers::receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message)
{
    if (senderType == DiagramType::Delivery && event == DiagramEventType::DeliveryIsHereEvent){
        emit startProcessEvent();
    } else {
        return;
    }
}

void Managers::wakeUp()
{
    emit sendMessage(diagramType(), DiagramEventType::StartEvent, "Начинаю работу");
    processTimer = new QTimer(this);
    processTimer->setInterval(3000);

    state = DiagramAgentState::Stopped;
}

void Managers::pauseAgents()
{
    oldProcessState = processTimer->isActive();
    processTimer->stop();
}

void Managers::continueAgents()
{
    if (oldProcessState)
        processTimer->start();
}

void Managers::onStartProcessEvent()
{
    emit sendMessage(diagramType(), DiagramEventType::ProcessStartEvent, "Разговариваем с доставкой...");
    state = DiagramAgentState::Working;

    connect(processTimer, &QTimer::timeout, this, &Managers::onEndProcessEvent);
    processTimer->start();
}

void Managers::onEndProcessEvent()
{
    emit sendMessage(diagramType(), DiagramEventType::ProcessEndEvent, "Договорились с доставкой");
    processTimer->stop();
}
