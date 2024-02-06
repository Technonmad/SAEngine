#ifndef TOOLSLIST_H
#define TOOLSLIST_H

#include <QAbstractListModel>
#include <QPixmap>
#include <QList>
#include <QStringList>

class ToolsList : public QAbstractListModel
{
   // Q_OBJECT

public:
    explicit ToolsList(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent) override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    QStringList mimeTypes() const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    Qt::DropActions supportedDropActions() const override;

    void addTool(const QPixmap &pixmap);

private:
    QList<QPixmap> tools;
};

#endif // TOOLSLIST_H
