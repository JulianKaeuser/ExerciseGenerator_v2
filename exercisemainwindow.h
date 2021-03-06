/********************************************************************************
** Form generated from reading UI file 'exercisemainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef EXERCISEMAINWINDOW_H
#define EXERCISEMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QCursor>
#include <QMouseEvent>

#include "animationdisplaywindow.h"
#include "timeslotdata.h"
#include "globaldata.h"
#include "smartpointers.h"
#include "toolutilities.h"
#include "paintlabel.h"

#ifndef __TIMESLOTIMAGEVECTOR_T
#define __TIMESLOTIMAGEVECTOR_T
typedef std::vector<QImage*> TimeslotImageVector;
#endif

QT_BEGIN_NAMESPACE

class Ui_ExerciseMainWindow : public QMainWindow
{
    Q_OBJECT

signals:

public slots:
    void assignSelectedTimeslotFieldCanvas(int);
    void addTimeSlot();
    void confirmDeletion();
    void changeSelectedToolColor(int);
    void changeCurrentCursorType(QListWidgetItem*);
    void openAnimationWindow();
    void closeAnimationWindowOnAction();
    void updateLCDNumber(QListWidgetItem*);
    void deleteSelectedTimeslot();
    void updateCurrentSelectedTimeslot(QListWidgetItem*);
    void updateCurrentSelectedTool(QListWidgetItem*);

    void rotateCurrentToolRight();
    void rotateCurrentToolLeft();


public:
    QAction *action_ber;
    QAction *actionHilfe;
    QAction *actionNeu;
    QAction *actionExportieren;
    QAction *actionLaden;
    QAction *actionSpeichern_unter;
    QAction *actionBeenden;
    QWidget *centralWidget;
    QListWidget *toolsListWidget;
    QLabel *toolsListWidgetDescriptorLabel;
    QFrame *line;
    QListWidget *timeslotsListWidget;
    QLabel *timeslotsListWidgetDescriptorLabel;
    QComboBox *timeslotFieldCanvasSelectComboBox;
    QPushButton *timeslotsAddPushButton;
    QPushButton *timeslotsDeletePushButton;
    QPushButton *toolRotateRightPushButton;
    QPushButton *toolRotateLeftPushButton;
    QComboBox *toolColorSelectComboBox;
    QSlider *gifSpeedSlider;
    QPushButton *animationShowPushButton;
    QCheckBox *animationLoopCheckbox;
    PaintLabel *activeTimeslotGraphicLabel;
    QLCDNumber *timeslotSelectedLCDNumber;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuBearbeiten;
    QMenu *menuInfo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    PaintLabel *arrowLabel = Q_NULLPTR;
    void addExerciseItem(ExerciseItem*);
    QCursor* getCurrentSelectedCursor();
    toolType getCurrentSelectedToolType();
    void repaintTimeSlot();

    bool labelNotClickable;



    void setupUi(Ui_ExerciseMainWindow *ExerciseMainWindow, int a);

    void retranslateUi(Ui_ExerciseMainWindow *ExerciseMainWindow);

protected:


private:
    Ui_ExerciseMainWindow *mw = Q_NULLPTR;

    // Which time slot is currently in selection
    QListWidgetItem* currentSelectedTimeslot = Q_NULLPTR;

    // which tool is currently in selection
    QListWidgetItem* currentSelectedTool = Q_NULLPTR;

    //Which cursor is currently active
    QCursor* currentSelectedCursor = Q_NULLPTR;

    // animation Player Window
    AnimationDisplayWindow *animationWindow = Q_NULLPTR;

    // global data storage
    globalData *globaldata = nullptr;

    // current tool type
    toolType currentToolType;

    int currentNumRotationsRight;
    int currentNumRotationsLeft;

    // avoid loop at one point
    bool repaintFlag = true;

    //methods
    void scaleActiveTimeslotGraphicsViewLabel(int);

    void storeCurrentProgressInGif();

    void buildTimeSlotsAnimations();

    TimeslotImageVector *builtTs = Q_NULLPTR;
    std::vector<int> *builtTsDurations = Q_NULLPTR;






};

namespace Ui {
    class ExerciseMainWindow: public Ui_ExerciseMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // EXERCISEMAINWINDOW_H
