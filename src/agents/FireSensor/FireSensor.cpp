#include "Firesensor.h"
#include "qgraphicsscene.h"

#include <QDateTime>
#include <QTimer>

Firesensor::Firesensor(QMenu *contextMenu, QGraphicsItem *parent)
    : GraphicsItem(GraphicsItem::FireSensor, contextMenu, parent)
{
    QPixmap pixmap(":/images/agents/fireSensor.png");
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pixmapItem = new QGraphicsPixmapItem(scaledPixmap);

}

Firesensor::~Firesensor()
{
    delete m_pixmapItem;
}

QRectF Firesensor::boundingRect() const
{
    return m_pixmapItem->boundingRect();
}

void Firesensor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_pixmapItem->paint(painter, option, widget);
}

void Firesensor::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

int Firesensor::type() const
{
    return Type;
}

QVariant Firesensor::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (Arrow *arrow: std::as_const(arrows))
            arrow->updatePosition();
    }

    return value;
}

void Firesensor::removeArrow(Arrow *arrow)
{
    arrows.removeAll(arrow);
}

void Firesensor::removeArrows()
{
    const auto arrowsCopy = arrows;
    for (Arrow *arrow : arrowsCopy) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void Firesensor::receiveMessage(DiagramType senderType, DiagramEventType event, const QString &message)
{
    if (event == DiagramEventType::FireEvent){
        emit sendMessage(diagramType(), DiagramEventType::FireEvent, "Пожар в " +
                         QVariant::fromValue(senderType).value<QString>());
    } else {
        return;
    }
}

void Firesensor::wakeUp()
{
    emit sendMessage(diagramType(), DiagramEventType::StartEvent, "Начинаю работу");
    state = DiagramAgentState::Working;
}

void Firesensor::pauseAgents()
{

}

void Firesensor::continueAgents()
{

}
