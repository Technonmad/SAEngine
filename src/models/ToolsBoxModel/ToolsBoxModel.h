#ifndef TOOLSBOXMODEL_H
#define TOOLSBOXMODEL_H

#include <QMimeData>
#include <QStandardItemModel>

class ToolsBoxModel: public QStandardItemModel
{
//    Q_OBJECT

public:
    ToolsBoxModel(QObject* parent = 0);

public:
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
};

#endif //TOOLSBOXMODEL_H
