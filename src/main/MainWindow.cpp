#include "MainWindow.h"
#include "Arrow/Arrow.h"

#include<QtWidgets>

MainWindow::MainWindow()
{
    createActions();
    createToolBox();
    createMenus();
    createTextBox();

    scene = new DiagramScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 1000, 1000));
    connect(scene, &DiagramScene::itemInserted,
            this, &MainWindow::itemInserted);
    connect(scene, &DiagramScene::messageSent,
            this, &MainWindow::messageFromItem);
    connect(this, &MainWindow::startAgents, scene, &DiagramScene::startAgents);
    createToolBars();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view, 4);
    layout->addWidget(textEdit, 1);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle("SAEngine");
    setUnifiedTitleAndToolBarOnMac(true);


}

void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
    for (QAbstractButton *myButton: buttons) {
        if (myButton != button)
            button->setChecked(false);
    }
    QString text = button->text();
    if (text == tr("White Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/backgrounds/background1.png"));
    else if (text == tr("Gray Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/backgrounds/background2.png"));
    else
        scene->setBackgroundBrush(QPixmap(":/images/backgrounds/background3.png"));

    scene->update();
    view->update();
}

void MainWindow::buttonGroupClicked(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttons = buttonGroup->buttons();
    for (QAbstractButton *myButton : buttons) {
        if (myButton != button)
            button->setChecked(false);
    }

    const int id = buttonGroup->id(button);
    scene->setItemType(GraphicsItem::DiagramType(id));
    scene->setMode(DiagramScene::InsertItem);
}

void MainWindow::processGroupClicked(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttons = processGroup->buttons();
    for (QAbstractButton *myButton : buttons) {
        if (myButton != button)
            button->setChecked(false);
    }

    const int id = buttonGroup->id(button);
    scene->setItemType(GraphicsItem::DiagramType(id));
    scene->setMode(DiagramScene::InsertItem);
}

void MainWindow::deleteItem()
{
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    for (QGraphicsItem *item : std::as_const(selectedItems)) {
        if (item->type() == Arrow::Type) {
            scene->removeItem(item);
            Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
            arrow->startItem()->removeArrow(arrow);
            arrow->endItem()->removeArrow(arrow);
            delete item;
        }
    }

    selectedItems = scene->selectedItems();
    for (QGraphicsItem *item : std::as_const(selectedItems)) {
        if (item->type() == GraphicsItem::Type)
            qgraphicsitem_cast<GraphicsItem *>(item)->removeArrows();
        scene->removeItem(item);
        delete item;
    }
}

void MainWindow::pointerGroupClicked()
{
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::bringToFront()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    for (const QGraphicsItem *item : overlapItems) {
        if (item->zValue() >= zValue && item->type() == GraphicsItem::Type)
            zValue = item->zValue() + 0.1;
    }

    selectedItem->setZValue(zValue);
}

void MainWindow::sendToBack()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    const QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    for (const QGraphicsItem *item : overlapItems) {
        if (item->zValue() >= zValue && item->type() == GraphicsItem::Type)
            zValue = item->zValue() - 0.1;
    }

    selectedItem->setZValue(zValue);
}

void MainWindow::itemInserted(GraphicsItem *item)
{
    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(int(item->diagramType()))->setChecked(false);
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QTransform oldMatrix = view->transform();
    view->resetTransform();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/toolbar/lineColor.png",
                                     qvariant_cast<QColor>(lineAction->data())));
    lineButtonTriggered();
}

void MainWindow::lineButtonTriggered()
{
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}

void MainWindow::startButtonTriggered()
{
    editToolBar->setDisabled(true);
    colorToolBar->setDisabled(true);
    pointerToolBar->setDisabled(true);
    startAction->setDisabled(true);
    toolBox->setDisabled(true);
    fileMenu->setDisabled(true);
    itemMenu->setDisabled(true);
    aboutMenu->setDisabled(true);
    view->setDisabled(true);
    stopAction->setDisabled(false);

    timer = new QTimer(this);
    timer->setInterval(10000);
    connect(timer, &QTimer::timeout, this,
            &MainWindow::startModelTriggered);
    timer->start();

    emit startAgents();
}

void MainWindow::stopButtonTriggered()
{
    editToolBar->setDisabled(false);
    colorToolBar->setDisabled(false);
    pointerToolBar->setDisabled(false);
    startAction->setDisabled(false);
    toolBox->setDisabled(false);
    fileMenu->setDisabled(false);
    itemMenu->setDisabled(false);
    aboutMenu->setDisabled(false);
    view->setDisabled(false);
    stopAction->setDisabled(true);

    timer->stop();
}

void MainWindow::startModelTriggered()
{
    int eventNumber = QRandomGenerator::global()->bounded(10) + 1;
    qDebug() << "Число: " << eventNumber;
}

void MainWindow::stopModelTriggered()
{

}

void MainWindow::messageFromItem(const QString &message)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    textEdit->append("[ " + currentTime.time().toString() + " ] " + message);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About SAEngine"),
                       tr("SAEngine is a virtual laboratory for testing and prototyping multiagent systems."));
}

void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::buttonGroupClicked);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("AICamera"), GraphicsItem::AICamera, ":/images/agents/cam.png"), 0, 0);
    layout->addWidget(createCellWidget(tr("Fire sensor"), GraphicsItem::FireSensor, ":/images/agents/fireSensor.png"), 0, 1);
    layout->addWidget(createCellWidget(tr("Firefighters"), GraphicsItem::Firefighters, ":/images/agents/firefighter.png"), 1, 0);
    layout->addWidget(createCellWidget(tr("Security"), GraphicsItem::SecurityPost, ":/images/agents/security.png"), 1, 1);
    layout->addWidget(createCellWidget(tr("Access control"), GraphicsItem::AccessControl, ":/images/agents/accessControl.png"), 2, 0);
    layout->addWidget(createCellWidget(tr("Engineers"), GraphicsItem::Engineers, ":/images/agents/engineers.png"), 2, 1);
    layout->addWidget(createCellWidget(tr("Managers"), GraphicsItem::Managers, ":/images/agents/managers.png"), 3, 0);
    layout->addWidget(createCellWidget(tr("Tecnician"), GraphicsItem::Tecnician, ":/images/agents/tecnician.png"), 3, 1);

    layout->setRowStretch(4, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    processGroup = new QButtonGroup(this);
    processGroup->setExclusive(false);
    connect(processGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::processGroupClicked);
    QGridLayout *processLayout = new QGridLayout;
    processLayout->addWidget(createCellWidget(tr("Storing"), GraphicsItem::Warehouse, ":/images/processes/warehouse.png"), 0, 0);
    processLayout->addWidget(createCellWidget(tr("Production"), GraphicsItem::ProductionLine, ":/images/processes/production.png"), 0, 1);
    processLayout->addWidget(createCellWidget(tr("Packaging"), GraphicsItem::PackingLine, ":/images/processes/packaging.png"), 1, 0);
    processLayout->addWidget(createCellWidget(tr("Delivery"), GraphicsItem::Delivery, ":/images/processes/delivery.png"), 1, 1);

    processLayout->setRowStretch(3, 10);
    processLayout->setColumnStretch(2, 10);

    QWidget *processWidget = new QWidget;
    processWidget->setLayout(processLayout);

    backgroundButtonGroup = new QButtonGroup(this);
    connect(backgroundButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::backgroundButtonGroupClicked);

    QGridLayout *backgroundLayout = new QGridLayout;
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
                                                           ":/images/backgrounds/background1.png"), 0, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
                                                           ":/images/backgrounds/background2.png"), 0, 1);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Background"),
                                                           ":/images/backgrounds/background3.png"), 1, 0);

    backgroundLayout->setRowStretch(2, 10);
    backgroundLayout->setColumnStretch(2, 10);

    QWidget *backgroundWidget = new QWidget;
    backgroundWidget->setLayout(backgroundLayout);

    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Agents"));
    toolBox->addItem(processWidget, tr("Processes"));
    toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}

void MainWindow::createActions()
{
    toFrontAction = new QAction(QIcon(":/images/toolbar/toFront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, &QAction::triggered, this, &MainWindow::bringToFront);

    sendBackAction = new QAction(QIcon(":/images/toolbar/toBack.png"),
                                tr("Send to &Back"), this);
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, &QAction::triggered, this, &MainWindow::sendToBack);

    deleteAction = new QAction(QIcon(":/images/toolbar/remove.png"),
                                tr("&Delete"), this);
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItem);

    startAction = new QAction(QIcon(":/images/toolbar/start.png"),
                              tr("&Start"), this);
    startAction->setStatusTip(tr("Start model"));
    connect(startAction, &QAction::triggered, this, &MainWindow::startButtonTriggered);
    // TODO: сделать действие

    stopAction = new QAction(QIcon(":/images/toolbar/stop.png"),
                              tr("&Stop"), this);
    stopAction->setStatusTip(tr("Stop model"));
    stopAction->setDisabled(true);
    connect(stopAction, &QAction::triggered, this, &MainWindow::stopButtonTriggered);
    // TODO: сделать действие

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit SAEngine"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);
//    TODO: make a save action
//    fileMenu->addAction(saveAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);

    modelMenu = menuBar()->addMenu(tr("&Model"));
    modelMenu->addAction(startAction);
    modelMenu->addAction(stopAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolBars()
{
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);

    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::red));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/toolbar/lineColor.png", Qt::red));
    connect(lineColorToolButton, &QAbstractButton::clicked,
            this, &MainWindow::lineButtonTriggered);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(lineColorToolButton);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/toolbar/pointer.png"));

    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/toolbar/linePointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(DiagramScene::InsertLine));
    connect(pointerTypeGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::pointerGroupClicked);

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, &QComboBox::currentTextChanged,
            this, &MainWindow::sceneScaleChanged);

    pointerToolBar = addToolBar(tr("Pointer type"));
    pointerToolBar->addWidget(pointerButton);
    pointerToolBar->addWidget(linePointerButton);
    pointerToolBar->addWidget(sceneScaleCombo);

    startToolBar = addToolBar(tr("Start type"));
    startToolBar->addAction(startAction);
    startToolBar->addAction(stopAction);
}

void MainWindow::createTextBox()
{
    textEdit = new QTextEdit;
    textEdit->setOverwriteMode(false);
    textEdit->setReadOnly(true);
    textEdit->setPlaceholderText("Здесь находится чат агентов");
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
    textEdit->setStyleSheet("QTextEdit { font-size: 14pt; }");
}

QWidget *MainWindow::createBackgroundCellWidget(const QString &text, const QString &image)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    backgroundButtonGroup->addButton(button);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignHCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

QWidget *MainWindow::createCellWidget(const QString &text, GraphicsItem::DiagramType type, const QString &image)
{
    QToolButton *button = new QToolButton;
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50,50));
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap image(imageFile);
    QPixmap scaledImage = image.scaled(50, 80, Qt::IgnoreAspectRatio, Qt::FastTransformation);

    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, scaledImage, source);

    return QIcon(pixmap);
}

QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}


QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt:: yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue") << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}
