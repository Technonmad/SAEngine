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
    ui->toolsList->setIconSize(QSize(100, 100));
    ui->toolsList->setResizeMode(QListWidget::Adjust);

    ui->toolsList->addItem(new QListWidgetItem(QIcon(QFileInfo(QDir("../"), "arm.png").absolutePath()), "elem1"));
    ui->toolsList->addItem(new QListWidgetItem(QIcon("arm.png"), "elem1"));
    ui->toolsList->addItem(new QListWidgetItem(QIcon("../arm.png"), "elem1"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

