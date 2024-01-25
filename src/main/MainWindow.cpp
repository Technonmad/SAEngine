#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QDir>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->toolsList->setViewMode(QListWidget::IconMode);
    ui->toolsList->setIconSize(QSize(50, 50));
    ui->toolsList->setResizeMode(QListWidget::Adjust);

    ui->toolsList->addItem(new QListWidgetItem(QIcon(":/images/tools/arm.png"), "elem1"));
    ui->toolsList->addItem(new QListWidgetItem(QIcon(":/images/tools/arm.png"), "elem2"));
    ui->toolsList->addItem(new QListWidgetItem(QIcon(":/images/tools/arm.png"), "elem3"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

