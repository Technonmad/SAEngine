#include <ToolsBoxModel/ToolsBoxModel.h>

enum Column{Name};

ToolsBoxModel::ToolsBoxModel(QObject *parent)
    :QAbstractItemModel(parent), rootItem(0)
{}

ToolsBoxModel::~ToolsBoxModel()
{
    delete rootItem;
}

Qt::ItemFlags ToolsBoxModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractItemModel::flags(index);
    if (index.isValid()){
        theFlags |= Qt::ItemIsSelectable | Qt::ItemIsEnabled;

        if (index.column() == Name){
            theFlags |= Qt::ItemIsDragEnabled;
        }
    }
    return theFlags;
}

QVariant ToolsBoxModel::data(const QModelIndex& index, int role) const
{
    if (!rootItem || !index.isValid() || index.column() < 0 || index.column() > 1)
        return QVariant();

    if (ToolsBoxItem *item = itemForIndex(index)) {

        if (role == Qt::DisplayRole) {
            if (index.column() == Name)
                return item->name();
        }

        if (role == Qt::DecorationRole && !m_icon.isNull())
            return m_icon;
    }

    return QVariant();
}

ToolsBoxItem *ToolsBoxModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (ToolsBoxItem *item = static_cast<ToolsBoxItem*>(index.internalPointer()))
            return item;
    }
    return rootItem;
}

QVariant ToolsBoxModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return tr("ToolGroup/Tool/...");
    }
    return QVariant();
}

int ToolsBoxModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    ToolsBoxItem* parentItem = itemForIndex(parent);
    return parentItem ? parentItem->childCount() : 0;
}

int ToolsBoxModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() && parent.column() != 0 ? 0 : 1;
}

QModelIndex ToolsBoxModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!rootItem || row < 0 || column < 0 || column >= 1 || (parent.isValid() && parent.column() != 0))
        return QModelIndex();

    ToolsBoxItem *parentItem = itemForIndex(parent);
    Q_ASSERT(parentItem);

    if (ToolsBoxItem *item = parentItem->childAt(row))
        return createIndex(row, column, item);

    return QModelIndex();
}

QModelIndex ToolsBoxModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    if (ToolsBoxItem* childItem = itemForIndex(index)) {
        if (ToolsBoxItem* parentItem = childItem->parent()) {
            if (parentItem == rootItem)
                return QModelIndex();
            if (ToolsBoxItem* grandParentItem = parentItem->parent()) {
                int row = grandParentItem->rowOfChild(parentItem);
                return createIndex(row, 0, parentItem);
            }
        }
    }
    return QModelIndex();
}

bool ToolsBoxModel::setHeaderData(int, Qt::Orientation, const QVariant &, int)
{
    return false;
}

bool ToolsBoxModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

