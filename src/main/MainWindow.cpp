#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "ToolsList.h"

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
    QFrame *frame = new QFrame;
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);

    toolsList = new QListView;
    toolsList->setDragEnabled(true);
    toolsList->setViewMode(QListView::IconMode);
    toolsList->setIconSize(QSize(50, 50));
    toolsList->setGridSize(QSize(70, 70));
    toolsList->setSpacing(10);
    toolsList->setMovement(QListView::Snap);

    ToolsList *toolsModel = new ToolsList(this);
    toolsList->setModel(toolsModel);

    frameLayout->addWidget(toolsList);
    setCentralWidget(frame);

}

