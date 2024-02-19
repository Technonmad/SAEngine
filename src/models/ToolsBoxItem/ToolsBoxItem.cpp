#include "ToolsBoxItem.h"

ToolsBoxItem::ToolsBoxItem(const QIcon &icon,
                           const QString &name,
                           ToolsBoxItem *parent)
    :m_name(name), m_parent(parent)
{
    if(m_parent)
        m_parent->addChild(this);
}

ToolsBoxItem::~ToolsBoxItem() { qDeleteAll(m_children); }

QString ToolsBoxItem::name() const { return m_name; }

void ToolsBoxItem::setName(const QString &name) { this->m_name = name; }

ToolsBoxItem *ToolsBoxItem::parent() const { return this->m_parent; }

bool ToolsBoxItem::hasChildren() const { return !m_children.isEmpty(); }

int ToolsBoxItem::childCount() const
{
    return m_children.count();
}

void ToolsBoxItem::addChild(ToolsBoxItem *item) {
    item->m_parent = this;
    this->m_children.append(item);
}

ToolsBoxItem *ToolsBoxItem::childAt(int row) const
{
    return m_children.value(row);
}

int ToolsBoxItem::rowOfChild(ToolsBoxItem *child) const
{
    return m_children.indexOf(child);
}
