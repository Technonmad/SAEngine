#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QAction>
#include <QComboBox>
#include <QToolBox>
#include <QToolButton>
#include <QMainWindow>
#include <QTextEdit>

#include <Item/GraphicsItem.h>

#include <DiagramScene/DiagramScene.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ToolsList;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

signals:
    void startModel();
    void stopModel();
    void startAgents();

private slots:
    void backgroundButtonGroupClicked(QAbstractButton *button);
    void buttonGroupClicked(QAbstractButton *button);
    void processGroupClicked(QAbstractButton *button);
    void deleteItem();
    void pointerGroupClicked();
    void bringToFront();
    void sendToBack();
    void itemInserted(GraphicsItem *item);
    void sceneScaleChanged(const QString &scale);
    void lineColorChanged();
    void lineButtonTriggered();
    void startButtonTriggered();
    void stopButtonTriggered();
    void startModelTriggered();
    void stopModelTriggered();
    void messageFromItem(const QString &message);
//    void itemSelected(QGraphicsItem *item);
    void about();
private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolBars();
    void createTextBox();
    QWidget *createBackgroundCellWidget(const QString &text,
                                        const QString &image);
    QWidget *createCellWidget(const QString &text,
                              GraphicsItem::DiagramType type,
                              const QString &image);

    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &imageFile, QColor color);
    QIcon createColorIcon(QColor color);

    DiagramScene *scene;
    QGraphicsView *view;

    QAction *exitAction;
    QAction *saveAction;
    QAction *addAction;
    QAction *deleteAction;
    QAction *startAction;
    QAction *stopAction;

    QAction *toFrontAction;
    QAction *sendBackAction;
    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;
    QMenu *modelMenu;

    QToolBar *editToolBar;
    QToolBar *colorToolBar;
    QToolBar *pointerToolBar;
    QToolBar *startToolBar;

    QTextEdit *textEdit;

    QComboBox *sceneScaleCombo;
    QComboBox *itemColorCombo;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *processGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QAction *fillAction;
    QAction *lineAction;

    QTimer *timer;
};
#endif // MAINWINDOW_H
