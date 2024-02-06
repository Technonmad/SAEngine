#include "GV_ModelWindow.h"

GV_ModelWindow::GV_ModelWindow(QWidget *widget)
{
    setAcceptDrops(true);
}

void GV_ModelWindow::dragEnterEvent(QDragEnterEvent *event)
{
   event->accept();
   event->acceptProposedAction();
}

void GV_ModelWindow::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void GV_ModelWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
    event->acceptProposedAction();
}

void GV_ModelWindow::dropEvent(QDropEvent *event)
{
    if (event->source() == this) return;

    QIcon *icon = qobject_cast<QIcon*>(event->source());

    QPixmap icon_image = icon->pixmap(50, 50);

    emit itemDrop(icon_image);
}
