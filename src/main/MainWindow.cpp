#include "MainWindow.h"
#include "Arrow/Arrow.h"

#include<QtWidgets>

MainWindow::MainWindow()
{
    createActions();
    createToolBox();
    createMenus();

    scene = new DiagramScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
//    connect(scene, &DiagramScene::itemInserted,
//            this, &MainWindow::itemInserted);
//    connect(scene, &DiagramScene::itemSelected,
//            this, &MainWindow::itemSelected);
    createToolBars();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);

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
        if (item->type() == Item::Type)
            qgraphicsitem_cast<Item *>(item)->removeArrows();
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
        if (item->zValue() >= zValue && item->type() == Item::Type)
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
        if (item->zValue() >= zValue && item->type() == Item::Type)
            zValue = item->zValue() - 0.1;
    }

    selectedItem->setZValue(zValue);
}

void MainWindow::itemInserted(Item *item)
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

//void MainWindow::itemColorChanged()
//{
//    fillAction = qobject_cast<QAction *>(sender());
//    fillColorToolButton->setIcon(createColorToolButtonIcon(
//                                     "",
//                                     qvariant_cast<QColor>(fillAction->data())));
//    fillButtonTriggered();
//}

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

void MainWindow::about()
{
    QMessageBox::about(this, tr("About SAEngine"),
                       tr("SAEngine is a virtual laboratory for testing and prototyping multiagent systems."));
}

//void MainWindow::itemSelected(QGraphicsItem *item)
//{

//}

//void MainWindow::fillButtonTriggered()
//{
//	scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
//}

void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::buttonGroupClicked);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("test1"), Item::Manager, ":/images/agents/arm.png"), 0, 0);
    layout->addWidget(createCellWidget(tr("test2"), Item::Customer, ":/images/agents/arm.png"), 0, 1);
    layout->addWidget(createCellWidget(tr("test1"), Item::Manager, ":/images/agents/arm.png"), 1, 0);
    layout->addWidget(createCellWidget(tr("test1"), Item::Manager, ":/images/agents/arm.png"), 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    processGroup = new QButtonGroup(this);
    processGroup->setExclusive(false);
    connect(processGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &MainWindow::processGroupClicked);
    QGridLayout *processLayout = new QGridLayout;
    processLayout->addWidget(createCellWidget(tr("test1"), Item::Warehouse, ":/images/agents/warehouse.png"), 0, 0);
    processLayout->addWidget(createCellWidget(tr("test2"), Item::ProductionLine, ":/images/agents/arm.png"), 0, 1);
    processLayout->addWidget(createCellWidget(tr("test1"), Item::PackingLine, ":/images/agents/warehouse.png"), 1, 0);
    processLayout->addWidget(createCellWidget(tr("test2"), Item::ProductionLine, ":/images/agents/arm.png"), 1, 1);

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
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/toolbar/lineColor.png", Qt::black));
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

QWidget *MainWindow::createCellWidget(const QString &text, Item::DiagramType type, const QString &image)
{
    Item item(type, itemMenu);
//    QIcon icon(item.image());

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
