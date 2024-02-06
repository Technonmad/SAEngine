#include "ToolsList.h"

#include <QIcon>
#include <QMimeData>


ToolsList::ToolsList(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant ToolsList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DecorationRole)
        return QIcon(tools.value(index.row()).scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    else if (role == Qt::UserRole)
        return tools.value(index.row());

    return QVariant();
}

Qt::ItemFlags ToolsList::flags(const QModelIndex &index) const
{
    if (index.isValid())
        return (QAbstractListModel::flags(index) | Qt::ItemIsDragEnabled);

    return Qt::ItemIsDropEnabled;
}

bool ToolsList::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    if(row >= tools.size() || row + count <= 0)
        return false;

    int beginRow = qMax(0, row);
    int endRow = qMin(row + count - 1, tools.size() - 1);

    beginRemoveRows(parent, beginRow, endRow);

    while (beginRow <= endRow) {
        tools.removeAt(beginRow);
        ++beginRow;
    }

    endRemoveRows();
    return true;
}

bool ToolsList::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (!data->hasFormat("image/x-tool"))
        return false;

    if (action == Qt::IgnoreAction)
        return true;

    if (column > 0)
        return false;

    int endCol;

    if (!parent.isValid()) {
        if (column < 0)
            endCol = tools.size();
        else
            endCol = qMin(column, tools.size());
    }
    else
        endCol = parent.column();

    QByteArray encodedData = data->data("image/x-tool");
    QDataStream stream(&encodedData, QDataStream::ReadOnly);

    while (!stream.atEnd()) {
        QPixmap pixmap;
        stream >> pixmap;

        beginInsertColumns(QModelIndex(), endCol, endCol);
        tools.insert(endCol, pixmap);
        endInsertColumns();

        ++endCol;
    }

    return true;
}

QMimeData *ToolsList::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QDataStream::WriteOnly);

    for (const QModelIndex &index: indexes) {
        if (index.isValid()) {
            QPixmap pixmap = qvariant_cast<QPixmap>(data(index, Qt::UserRole));
            stream << pixmap;
        }
    }

    mimeData->setData("image/x-tool", encodedData);
    return mimeData;
}

QStringList ToolsList::mimeTypes() const
{
    QStringList types;
    types << "image/x-tool";
    return types;
}

int ToolsList::rowCount(const QModelIndex &parent) const
{
    return 1;
}

int ToolsList::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : tools.size();
}

Qt::DropActions ToolsList::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

void ToolsList::addTool(const QPixmap &pixmap)
{
    beginInsertColumns(QModelIndex(), tools.size(), tools.size());
    tools.insert(tools.size(), pixmap);
    endInsertColumns();
}
