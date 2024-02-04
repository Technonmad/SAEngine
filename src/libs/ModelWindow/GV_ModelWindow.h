#ifndef GV_MODELWINDOW_H
#define GV_MODELWINDOW_H

#include <QGraphicsView>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QIcon>
#include <QPixmap>

class GV_ModelWindow : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GV_ModelWindow(QWidget *widget = nullptr);
signals:
    void itemDrop(QIcon);
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // GV_MODELWINDOW_H
