#ifndef TOOLSBOXMODEL_H
#define TOOLSBOXMODEL_H

#include <QAbstractItemModel>
#include <QIcon>
#include <ToolsBoxItem/ToolsBoxItem.h>

class ToolsBoxModel: public QAbstractItemModel
{
public:
    explicit ToolsBoxModel(QObject* parent = 0);

    ~ToolsBoxModel();

    Qt::ItemFlags flags(const QModelIndex& index) const;

    QVariant data() const;

    ToolsBoxItem* itemForIndex(const QModelIndex& index) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    int rowCount(const QModelIndex& parent) const;

    int columnCount(const QModelIndex& parent) const;

    QModelIndex index(int row, int column, const QModelIndex& parent) const;

private:
    QString m_toolName;
    QIcon m_icon;
    ToolsBoxItem* rootItem;
};

#endif //TOOLSBOXMODEL_H
