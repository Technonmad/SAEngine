#include <ToolsBoxModel/ToolsBoxModel.h>

ToolsBoxModel::ToolsBoxModel(QObject *parent)
    : QStandardItemModel(parent)
{}

QMimeData *ToolsBoxModel::mimeData(const QModelIndexList &indexes) const
{
    if (indexes.isEmpty())
        return nullptr;

    QMimeData* mimeData = new QMimeData();
    QString text;

    for (const QModelIndex& index: indexes) {
        if (index.isValid()) {
            text = index.data(Qt::DisplayRole).toString();
            break;
        }
    }

    std::unique_ptr<QByteArray> encodedData(new QByteArray(text.toUtf8()));
    mimeData->setData("text/plain", *encodedData);
    return mimeData;
}

bool ToolsBoxModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    return false;
}

