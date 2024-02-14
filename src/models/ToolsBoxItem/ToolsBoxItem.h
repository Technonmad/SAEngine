#ifndef TOOLSBOXITEM_H
#define TOOLSBOXITEM_H

#include <QIcon>


class ToolsBoxItem
{
public:
    explicit ToolsBoxItem(const QIcon& icon,
                         const QString& name,
                         ToolsBoxItem* parent=0);

    ~ToolsBoxItem();

    QString name() const;
    void setName(const QString& name);
    ToolsBoxItem* parent() const;
    bool hasChildren() const;
    void addChild(ToolsBoxItem* item);

private:
    QString m_name;
    ToolsBoxItem* m_parent;
    QList<ToolsBoxItem*> m_children;
};

#endif // TOOLSBOXITEM_H
