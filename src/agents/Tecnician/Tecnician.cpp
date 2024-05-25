#include "Tecnician.h"
#include "qgraphicsscene.h"

#include <QDateTime>
#include <QTimer>

Tecnician::Tecnician(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::Tecnician, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/tecnician.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);

    connect(this, &Tecnician::startProcessEvent, this, &Tecnician::onStartProcessEvent);
}

Tecnician::~Tecnician()
{
    delete m_pixmapItem;
}

QRectF Tecnician::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Tecnician::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Tecnician::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Tecnician::type() const
{
    return Type;
}

QVariant Tecnician::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Tecnician::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Tecnician::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Tecnician::receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message)
{
    if (event == DiagramEventType::BrakeEvent){
        emit startProcessEvent();
    } else {
        return;
    }
}

void Tecnician::wakeUp()
{
    emit sendMessage(diagramType(), DiagramEventType::StartEvent, "Начинаю работу");
    processTimer = new QTimer(this);
    processTimer->setInterval(7000);

    state = DiagramAgentState::Stopped;

}

void Tecnician::pauseAgents()
{
    oldProcessState = processTimer->isActive();
    processTimer->stop();
}

void Tecnician::continueAgents()
{
    if (oldProcessState)
        processTimer->start();
}

void Tecnician::onStartProcessEvent()
{
    emit sendMessage(diagramType(), DiagramEventType::ProcessStartEvent, "Чиним...");
    state = DiagramAgentState::Working;

    connect(processTimer, &QTimer::timeout, this, &Tecnician::onEndProcessEvent);
    processTimer->start();
}

void Tecnician::onEndProcessEvent()
{
    emit sendMessage(diagramType(), DiagramEventType::RepairEvent, "Починили");
    processTimer->stop();
}
