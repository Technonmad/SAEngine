#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include<QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupWidgets();
    /*ui->toolsList->setIconSize(QSize(50, 50));

    ui->toolsList->addTool(QPixmap(":/images/tools/arm.png"));
    ui->toolsList->addTool(QPixmap(":/images/tools/arm.png"));
    ui->toolsList->addTool(QPixmap(":/images/tools/arm.png")); */

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWidgets()
{

}

