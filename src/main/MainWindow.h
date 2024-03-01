#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ToolsBoxModel/ToolsBoxModel.h"
#include <QMainWindow>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ToolsList;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSharedPointer<ToolsBoxModel> model;
    QSharedPointer<QStandardItem> item1;
    QSharedPointer<QStandardItem> item2;
    QSharedPointer<QStandardItem> item3;
};
#endif // MAINWINDOW_H
