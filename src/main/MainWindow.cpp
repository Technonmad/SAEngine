#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include<QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = QSharedPointer<ToolsBoxModel>::create();
    QStandardItem *rootItem = model->invisibleRootItem();
    rootItem->setText("Инструменты");

    item1 =
            QSharedPointer<QStandardItem>::create(QIcon("C:/Users/trata/Downloads/process.png"), "Elem1");
    item2 =
            QSharedPointer<QStandardItem>::create(QIcon("C:/Users/trata/Downloads/process.png"), "Elem2");
    item3 =
            QSharedPointer<QStandardItem>::create(QIcon("C:/Users/trata/Downloads/process.png"), "Elem3");
    rootItem->appendRow(item1.get());
    rootItem->appendRow(item2.get());
    item1.get()->appendRow(item3.get());

    ui->toolsView->setHeaderHidden(true);

    ui->toolsView->setModel(model.get());

}

MainWindow::~MainWindow()
{
    delete ui;
}

