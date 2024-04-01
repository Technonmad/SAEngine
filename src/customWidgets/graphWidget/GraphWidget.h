#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

class GraphWidget: public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, /*InsertText, */MoveItem };

    explicit GraphWidget(QMenu *itemMenu, QObject *parent = nullptr);
    QColor lineColor() const;
    void setLineColor(const QColor &color);

public slots:
    void setMode(Mode mode);
    void setItemType(DiagramItem::DiagramType type);
    void editorLostFocus(DiagramTextItem *item);

signals:
    void itemInserted(DiagramItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    bool isItemChange(int type) const;

    DiagramItem::DiagramType myItemType;
    QMenu *myItemMenu;
    QGraphicsLineItem *line;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QColor myLineColor;
};
#endif // GRAPHWIDGET_H
