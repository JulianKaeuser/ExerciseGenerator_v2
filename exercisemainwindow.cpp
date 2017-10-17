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
#include <QMessageBox>
#include <QPainter>
#include <QString>
#include <QGraphicsItem>

#include "qgifimage.h"

#include "exercisemainwindow.h"

#include <iostream>
#include <iterator>
#include <utility>
#include <memory>
#include <list>
//#include "smartpointers.h"

#define PATH  ("/home/juliankaeuser/Dokumente/Eishockey/Coding/ExerciseGenerator_v2/imageSources/tempGif.gif")

#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

#define TIMESLOTDATA(ts) ((*(globaldata->timeslots))[(ts)])

#define OFFSET_POINT_LARGE(x) ((x += QPoint(20, 0)))
#define OFFSET_POINT_SMALL(x) ((x += QPoint(5, 0)))






/**
 * @brief Ui_ExerciseMainWindow::assignSelectedTimeslotFieldCanvas
 * @param fieldCanvasType
 */
void Ui_ExerciseMainWindow::assignSelectedTimeslotFieldCanvas(int fieldCanvasType){
    //DEBUG(assignSelectedTimeSlotFieldCanvas(int) called);
    /*
     * fieldCanvasTypes:
     * 0 = full
     * 1 = full90
     * 2 = third
     * 3 = half
     * 4 = middle
     * 1000 = unused;
     */

    TimeslotData *ts = (*(globaldata->timeslots))[currentSelectedTimeslotItem];
    canvasType type = static_cast<canvasType>(fieldCanvasType);

    QImage *im =  ( new QImage(":/imageSources/fullFieldCanvas.png"));
       switch(type){
            case(full):{
                im = new QImage(":/imageSources/fullFieldCanvas.png");

                break;
            }
            case(full90):{
                im= new QImage(":/imageSources/fullField90Canvas.png");
                break;
            }
            case(third):{
                im= new QImage(":/imageSources/thirdFieldCanvas.png");
                break;
            }
            case(half):{
                im= new QImage(":/imageSources/halfFieldCanvas.png");
                break;
            }
            case(middle):{
                im= new QImage(":/imageSources/middleFieldCanvas.png");
                break;
            }
            default:
                return;
            }
       ts->ct = type;

};

/**
  Adds a timeslot to the data base and the widget list
 * @brief Ui_ExerciseMainWindow::addTimeSlot
 */
void Ui_ExerciseMainWindow::addTimeSlot(){
    DEBUG(addTimeSlot() called);
    int previousNrTimeslots = timeslotsListWidget->count();

    int newIndex = previousNrTimeslots+1;

    QImage *im = new QImage("qrc:/imageSources/fullFieldCanvas.png");


    QListWidgetItem *newTs = new QListWidgetItem(timeslotsListWidget);
    (*(globaldata->timeslots))[(newTs)] = (new TimeslotData(newIndex,  timeslotsListWidget->row(newTs), (newTs), Q_NULLPTR, (im), canvasType::full90, new QGraphicsScene(centralWidget)));

    QListWidgetItem *prevTs = currentSelectedTimeslotItem;
    currentSelectedTimeslotItem = newTs;
    assignSelectedTimeslotFieldCanvas(0);

    timeslotsListWidget->setCurrentItem(newTs);


    QString qstr(std::to_string(newIndex).c_str());
    newTs->setText(qstr);

};

// confirm whether the currently selected timeslot shall be deleted
void Ui_ExerciseMainWindow::confirmDeletion(){
    QMessageBox msgBox(
                QMessageBox::Question,
                "Zeitschritt löschen?",
                "ausgewählten Zeitschritt löschen?",
                QMessageBox::Yes | QMessageBox::No);

    msgBox.setButtonText(QMessageBox::Yes, "Ja");
    msgBox.setButtonText(QMessageBox::No, "Nein");

    if (msgBox.exec() == QMessageBox::No) {
        return;
    }
    else{
        deleteSelectedTimeslot();
    }

};//confirmDeletion

/**
 * @brief Ui_ExerciseMainWindow::rotateCurrentToolLeft
 */
void Ui_ExerciseMainWindow::rotateCurrentToolLeft(){
    currentTool->rotate(-45);
    mw->setCursor(*(currentTool->getCursor()));
}; //rotateCurrentToolLeft

/**
 * @brief Ui_ExerciseMainWindow::rotateCurrentToolRight
 */
void Ui_ExerciseMainWindow::rotateCurrentToolRight(){
    currentTool->rotate(45);
    mw->setCursor(*(currentTool->getCursor()));
}; //rotateCurrentToolRight

/**
 * @brief Ui_ExerciseMainWindow::changeSelectedToolColor
 * @param colorIndex
 */
void Ui_ExerciseMainWindow::changeSelectedToolColor(int colorIndex){
    QColor color = getColorFromBox(toolColorSelectComboBox);
    currentTool->setColor(color);
    this->mw->setCursor(*(currentTool->getCursor()));
};//changeSelesctedToolColor

/**
 * @brief Ui_ExerciseMainWindow::changeCurrentToolType
 * @param exerciseItem
 */
void Ui_ExerciseMainWindow::changeCurrentToolType(QListWidgetItem* exerciseItem){
    DEBUG(changeCurrentToolType() called);
    Tool* oldTool = this->currentTool;
    Tool* newTool = new Tool(static_cast<toolType>(toolsListWidget->row(exerciseItem)), getColorFromBox(toolColorSelectComboBox), 0);
    this->currentTool = newTool;
    this->mw->setCursor( *(currentTool->getCursor()));
    //if(oldTool!=Q_NULLPTR){
    //    delete(oldTool);
    //}
    DEBUG(changeCurrentToolType() finished);
};//changeCurrentToolType

/**
  open separate Window for animation player
*/
void Ui_ExerciseMainWindow::openAnimationWindow(){
    this->buildTimeSlotsAnimations();
    this->storeCurrentProgressInGif();
    animationWindow = new AnimationDisplayWindow(gifSpeedSlider->value(), animationLoopCheckbox->isChecked(), PATH);
    animationWindow->show();
};

/**
  close the animation window on every other action
 * @brief Ui_ExerciseMainWindow::closeAnimationWindowOnAction
 */
void Ui_ExerciseMainWindow::closeAnimationWindowOnAction(){
    //DEBUG(closeAnimationWindowOnAction() called);
    if(animationWindow!=Q_NULLPTR){
        animationWindow->close();
        //delete animationWindow;
        animationWindow = Q_NULLPTR;
    }
};

/**
 * @brief Ui_ExerciseMainWindow::updateLCDNumber
 * @param selectedTimeSlotItem
 */
void Ui_ExerciseMainWindow::updateLCDNumber(QListWidgetItem* selectedTimeSlotItem){
    DEBUG(updateLCDNumber(QListWidgetItem*) called);
    int indexOfItem = timeslotsListWidget->row(selectedTimeSlotItem);

    timeslotSelectedLCDNumber->display(indexOfItem+1);

}; //updateLCDNumber

/**
 * @brief Ui_ExerciseMainWindow::deleteSelectedTimeslot
 */
void Ui_ExerciseMainWindow::deleteSelectedTimeslot(){
    DEBUG(deleteSelectedTimeslot() called);
    // do not delete if nothing left then
    if (timeslotsListWidget->count()<2){
        DEBUG(less than 2 slots);
       TimeslotData* ts =  (*( globaldata->timeslots))[currentSelectedTimeslotItem];
       ts->objects.clear();
       canvasType ct = ts->ct;
               ts->ct = canvasType::unused;
       assignSelectedTimeslotFieldCanvas(ct);

        repaintTimeSlot();
        return;
    }
    if(currentSelectedTimeslotItem==Q_NULLPTR){
        DEBUG(nullpointer for currentSelectedTimeslotItem);
        return;
    }

    // delete the one to delete

    QListWidgetItem *toDelete = (currentSelectedTimeslotItem);

    int newIndex = timeslotsListWidget->currentRow()-1;
    if (newIndex <0) newIndex = 0;
   // currentSelectedTimeslotItem = timeslotsListWidget->itemAt(0, newIndex);
    this->globaldata->timeslots->erase(toDelete);
    timeslotsListWidget->takeItem(timeslotsListWidget->row(toDelete));
   // timeslotsListWidget->takeItem(timeslotsListWidget->currentRow());
   // delete toDelete;

    // assign new numbers and texts
    std::list<TimeslotData> *timeslotList = new std::list<TimeslotData>();
    for (auto iter = globaldata->timeslots->begin(); iter != globaldata->timeslots->end(); ++iter){
        timeslotList->emplace_back(*((*iter).second) );
    }
    timeslotList->sort();
    int ii = 1;
    for (auto iter = timeslotList->begin(); iter != timeslotList->end(); ++iter){
        (*iter).item->setText(std::to_string(ii).c_str());
        (*iter).number = ii;
        ii++;
    }
    updateCurrentSelectedTimeslotItem(timeslotsListWidget->item(newIndex));
}; // deleteSelectedTimeSlot


/**
 * @brief Ui_ExerciseMainWindow::updatecurrentSelectedTimeslotItem
 * @param clickedItem
 */
void Ui_ExerciseMainWindow::updateCurrentSelectedTimeslotItem(QListWidgetItem* clickedItem){
    DEBUG(updatecurrentSelectedTimeslotItem(QListWidgetItem* ) called);
    this->currentSelectedTimeslotItem = clickedItem;
    int comboBoxIndex = 0;
    if((*(globaldata->timeslots))[(clickedItem)] !=nullptr){
        comboBoxIndex = static_cast<int>((*(globaldata->timeslots))[(clickedItem)]->ct);
    }

    this->timeslotFieldCanvasSelectComboBox->setCurrentIndex(comboBoxIndex);


} // updatecurrentSelectedTimeslotItem

/**
 * @brief Ui_ExerciseMainWindow::updateCurrentSelectedToolItem
 * @param clickedItem
 */
void Ui_ExerciseMainWindow::updateCurrentSelectedToolItem(QListWidgetItem* clickedItem){
    this->currentSelectedToolItem = clickedItem;

} // updateCurrentSelectedTool

/**
 * @brief Ui_ExerciseMainWindow::addExerciseItem
 * @param item
 */
void Ui_ExerciseMainWindow::addExerciseItem(ExerciseItem *item){
    (*(this->globaldata->timeslots))[currentSelectedTimeslotItem]->objects.emplace_back(item);
    //DEBUG(item added);
};

/**
 * @brief Ui_ExerciseMainWindow::getCurrentSelectedCursor
 */
QCursor* Ui_ExerciseMainWindow::getCurrentSelectedCursor(){
    return currentTool->getCursor();
};

/**
 * @brief Ui_ExerciseMainWindow::getCurrentSelectedToolType
 * @return
 */
Tool* Ui_ExerciseMainWindow::getCurrentSelectedToolType(){
    return currentTool;
};

void Ui_ExerciseMainWindow::repaintTimeSlot(){
  TimeslotData *ts = (*(this->globaldata->timeslots))[currentSelectedTimeslotItem];


}; // repaintTimeSlot()

void Ui_ExerciseMainWindow::setupUi(Ui_ExerciseMainWindow *ExerciseMainWindow, int a)
    {
        this->mw = ExerciseMainWindow;
        /*
         * Basic Window settings
         */
        if (ExerciseMainWindow->objectName().isEmpty())
            ExerciseMainWindow->setObjectName(QStringLiteral("ExerciseMainWindow"));
        ExerciseMainWindow->resize(1200, 685);
        ExerciseMainWindow->setFixedSize(1200,685);
        ExerciseMainWindow->setMouseTracking(true);


        centralWidget = new QWidget(ExerciseMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));

        /*
         * Basic storage and data structures
         */
        this->globaldata = new globalData;
        globaldata->id = 1;
        globaldata->path = Q_NULLPTR;
        globaldata->timeslots = new std::map<QListWidgetItem*, TimeslotData*>;

        /*
         * Menu Actions
         */
        action_ber = new QAction(ExerciseMainWindow);
        action_ber->setObjectName(QStringLiteral("action_ber"));
        actionHilfe = new QAction(ExerciseMainWindow);
        actionHilfe->setObjectName(QStringLiteral("actionHilfe"));
        actionNeu = new QAction(ExerciseMainWindow);
        actionNeu->setObjectName(QStringLiteral("actionNeu"));
        actionExportieren = new QAction(ExerciseMainWindow);
        actionExportieren->setObjectName(QStringLiteral("actionExportieren"));
        actionLaden = new QAction(ExerciseMainWindow);
        actionLaden->setObjectName(QStringLiteral("actionLaden"));
        actionSpeichern_unter = new QAction(ExerciseMainWindow);
        actionSpeichern_unter->setObjectName(QStringLiteral("actionSpeichern_unter"));
        actionBeenden = new QAction(ExerciseMainWindow);
        actionBeenden->setObjectName(QStringLiteral("actionBeenden"));

        /*
         * list of available tools
         */
        toolsListWidget = new QListWidget(centralWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        new QListWidgetItem(toolsListWidget);
        toolsListWidget->setObjectName(QStringLiteral("toolsListWidget"));
        toolsListWidget->setGeometry(QRect(990, 50, 140, 210));
        toolsListWidgetDescriptorLabel = new QLabel(centralWidget);
        toolsListWidgetDescriptorLabel->setObjectName(QStringLiteral("toolsListWidgetDescriptorLabel"));
        toolsListWidgetDescriptorLabel->setGeometry(QRect(990, 30, 85, 20));

        /*
         * ComboBox to select color of tool
         */
        toolColorSelectComboBox = new QComboBox(centralWidget);
        toolColorSelectComboBox->setObjectName(QStringLiteral("toolColorSelectComboBox"));
        toolColorSelectComboBox->setGeometry(QRect(1060, 270, 85, 30));

        /*
         * Rotation of tool
         */
        toolRotateRightPushButton = new QPushButton(centralWidget);
        toolRotateRightPushButton->setObjectName(QStringLiteral("toolRotateRightPushButton"));
        toolRotateRightPushButton->setGeometry(QRect(1135, 170, 60, 30));

        toolRotateLeftPushButton = new QPushButton(centralWidget);
        toolRotateLeftPushButton->setObjectName(QStringLiteral("toolRotateLeftPushButton"));
        toolRotateLeftPushButton->setGeometry(QRect(1135, 205, 60, 30));


        // separator line for tool area
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(980, 0, 16, 641));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        /*
         * Timeslots view list
         */
        timeslotsListWidget = new QListWidget(centralWidget);
        new QListWidgetItem(timeslotsListWidget);
        timeslotsListWidget->setObjectName(QStringLiteral("timeslotsListWidget"));
        timeslotsListWidget->setGeometry(QRect(990, 330, 61, 171));
        timeslotsListWidget->setMouseTracking(true);
        timeslotsListWidgetDescriptorLabel = new QLabel(centralWidget);
        timeslotsListWidgetDescriptorLabel->setObjectName(QStringLiteral("timeslotsListWidgetDescriptorLabel"));
        timeslotsListWidgetDescriptorLabel->setGeometry(QRect(990, 310, 81, 20));

        /*
         * ComboBox to select Field canvas
         */
        timeslotFieldCanvasSelectComboBox = new QComboBox(centralWidget);
        timeslotFieldCanvasSelectComboBox->setObjectName(QStringLiteral("timeslotFieldCanvasSelectComboBox"));
        timeslotFieldCanvasSelectComboBox->setGeometry(QRect(1060, 410, 85, 30));

        /*
         * button to add timeslots
         */
        timeslotsAddPushButton = new QPushButton(centralWidget);
        timeslotsAddPushButton->setObjectName(QStringLiteral("timeslotsAddPushButton"));
        timeslotsAddPushButton->setGeometry(QRect(1060, 330, 85, 30));

        /*
         * button to delete timeslots
         */
        timeslotsDeletePushButton = new QPushButton(centralWidget);
        timeslotsDeletePushButton->setObjectName(QStringLiteral("timeslotsDeletePushButton"));
        timeslotsDeletePushButton->setGeometry(QRect(1060, 370, 85, 30));


        /*
         *  Animation Toggling
         */
        gifSpeedSlider = new QSlider(centralWidget);
        gifSpeedSlider->setObjectName(QStringLiteral("gifSpeedSlider"));
        gifSpeedSlider->setGeometry(QRect(1000, 590, 160, 16));
        gifSpeedSlider->setOrientation(Qt::Horizontal);
        animationShowPushButton = new QPushButton(centralWidget);
        animationShowPushButton->setObjectName(QStringLiteral("animationShowPushButton"));
        animationShowPushButton->setGeometry(QRect(1000, 530, 141, 28));
        animationLoopCheckbox = new QCheckBox(centralWidget);
        animationLoopCheckbox->setObjectName(QStringLiteral("animationLoopCheckbox"));
        animationLoopCheckbox->setGeometry(QRect(1000, 560, 91, 26));


        /*
         * Graphics Scene (usually current)
         */
        graphicScene = new QGraphicsScene(centralWidget);
        graphicScene->setObjectName(QStringLiteral("graphicsScene"));
        graphicScene->addItem(new QGraphicsPixmapItem(QPixmap::fromImage(QImage(":imageSources/fullFieldCanvas.png").scaled(QSize(660, 470), Qt::KeepAspectRatio))));

        // graphics View
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setGeometry(QRect(140,90,670,480));
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setScene(graphicScene);


        // LCD to show number of selected step
        timeslotSelectedLCDNumber = new QLCDNumber(centralWidget);
        timeslotSelectedLCDNumber->setObjectName(QStringLiteral("timeslotSelectedLCDNumber"));
        timeslotSelectedLCDNumber->setGeometry(QRect(740, 50, 64, 23));
        timeslotSelectedLCDNumber->setStyleSheet(QStringLiteral("font: 11pt \"Cantarell\";"));

        /*
         * Other stuff
         */
        ExerciseMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ExerciseMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1196, 25));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QStringLiteral("menuDatei"));
        menuBearbeiten = new QMenu(menuBar);
        menuBearbeiten->setObjectName(QStringLiteral("menuBearbeiten"));
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName(QStringLiteral("menuInfo"));
        ExerciseMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ExerciseMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ExerciseMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ExerciseMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ExerciseMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuBearbeiten->menuAction());
        menuBar->addAction(menuInfo->menuAction());
        menuDatei->addAction(actionNeu);
        menuDatei->addSeparator();
        menuDatei->addAction(actionExportieren);
        menuDatei->addSeparator();
        menuDatei->addAction(actionLaden);
        menuDatei->addAction(actionSpeichern_unter);
        menuDatei->addAction(actionBeenden);
        menuInfo->addAction(action_ber);
        menuInfo->addSeparator();
        menuInfo->addAction(actionHilfe);

        retranslateUi(ExerciseMainWindow);
        /*
         * Initial values for stuff
         */
        timeslotsListWidget->setCurrentRow(0);
        updateLCDNumber(timeslotsListWidget->item(0));

        // current selected Time slot
        this->currentSelectedTimeslotItem = timeslotsListWidget->item(0);



        //this->setMouseTracking(true);
        mw->setMouseTracking(true);
        /*
         * Slot connections
         */

        //
        //QObject::connect(timeslotsListWidget, SIGNAL(currentRowChanged(int)), toolColorSelectComboBox, SLOT(setCurrentIndex(int)));

        // when Field Canvas Combo box changes, adjust timeslot and
        QObject::connect(timeslotFieldCanvasSelectComboBox, SIGNAL(currentIndexChanged(int)), ExerciseMainWindow, SLOT(assignSelectedTimeslotFieldCanvas(int)));

        // when user clicks addPushButton, new timeslot is created
        QObject::connect(timeslotsAddPushButton, SIGNAL(clicked()), ExerciseMainWindow, SLOT(addTimeSlot()));


        // delete selcted timeslot
        QObject::connect(timeslotsDeletePushButton, SIGNAL(clicked()), ExerciseMainWindow, SLOT(confirmDeletion()));

        // rotate tools
        QObject::connect(toolRotateLeftPushButton, SIGNAL(clicked(bool)), ExerciseMainWindow, SLOT(rotateCurrentToolLeft()));
        QObject::connect(toolRotateRightPushButton, SIGNAL(clicked(bool)), ExerciseMainWindow, SLOT(rotateCurrentToolRight()));


        QObject::connect(toolColorSelectComboBox, SIGNAL(currentIndexChanged(int)), ExerciseMainWindow, SLOT(changeSelectedToolColor(int)));


        // open animation window
        QObject::connect(animationShowPushButton, SIGNAL(clicked()), ExerciseMainWindow, SLOT(openAnimationWindow()));


        // painting

        /*
         * For all clicks, close the animation window
         */
        QObject::connect(animationLoopCheckbox, SIGNAL(clicked()), ExerciseMainWindow, SLOT(closeAnimationWindowOnAction()));
        QObject::connect(gifSpeedSlider, SIGNAL(sliderMoved(int)), ExerciseMainWindow, SLOT(closeAnimationWindowOnAction()));
        QObject::connect(timeslotFieldCanvasSelectComboBox, SIGNAL(currentIndexChanged(int)), ExerciseMainWindow, SLOT(closeAnimationWindowOnAction()));

        QObject::connect(timeslotsDeletePushButton, SIGNAL(clicked()), ExerciseMainWindow, SLOT(closeAnimationWindowOnAction()));
        QObject::connect(toolColorSelectComboBox, SIGNAL(activated(int)), ExerciseMainWindow, SLOT(closeAnimationWindowOnAction()));
        QObject::connect(toolsListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), ExerciseMainWindow, SLOT(closeAnimationWindowOnAction()));
        QObject::connect(timeslotsAddPushButton, SIGNAL(clicked()), ExerciseMainWindow, SLOT(closeAnimationWindowOnAction()));

        // clicks in timeslotListWidget
        QObject::connect(timeslotsListWidget, SIGNAL(itemClicked(QListWidgetItem*)), ExerciseMainWindow, SLOT(updateLCDNumber(QListWidgetItem*)));
        QObject::connect(timeslotsListWidget, SIGNAL(itemClicked(QListWidgetItem*)), ExerciseMainWindow, SLOT(updateCurrentSelectedTimeslotItem(QListWidgetItem*)));

        // clicks on toolsListWidget
        QObject::connect(toolsListWidget, SIGNAL(itemClicked(QListWidgetItem*)), ExerciseMainWindow, SLOT(updateCurrentSelectedToolItem(QListWidgetItem*)));
        QObject::connect(toolsListWidget, SIGNAL(itemClicked(QListWidgetItem*)), ExerciseMainWindow, SLOT(changeCurrentToolType(QListWidgetItem*)));

        QMetaObject::connectSlotsByName(ExerciseMainWindow);
    } // setupUi

void Ui_ExerciseMainWindow::retranslateUi(Ui_ExerciseMainWindow *ExerciseMainWindow)
    {
        ExerciseMainWindow->setWindowTitle(QApplication::translate("ExerciseMainWindow", "ExerciseMainWindow", Q_NULLPTR));
        action_ber->setText(QApplication::translate("ExerciseMainWindow", "\303\234ber", Q_NULLPTR));
        actionHilfe->setText(QApplication::translate("ExerciseMainWindow", "Hilfe", Q_NULLPTR));
        actionNeu->setText(QApplication::translate("ExerciseMainWindow", "Neu", Q_NULLPTR));
        actionExportieren->setText(QApplication::translate("ExerciseMainWindow", "Exportieren", Q_NULLPTR));
        actionLaden->setText(QApplication::translate("ExerciseMainWindow", "Laden", Q_NULLPTR));
        actionSpeichern_unter->setText(QApplication::translate("ExerciseMainWindow", "Speichern unter", Q_NULLPTR));
        actionBeenden->setText(QApplication::translate("ExerciseMainWindow", "Beenden", Q_NULLPTR));


        /*
         * tool list
         */
        const bool __sortingEnabled = toolsListWidget->isSortingEnabled();
        toolsListWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = toolsListWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("ExerciseMainWindow", "Spieler", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem1 = toolsListWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("ExerciseMainWindow", "St\303\274rmer", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem2 = toolsListWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("ExerciseMainWindow", "St\303\274rmer+Puck", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem3 = toolsListWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("ExerciseMainWindow", "Verteidiger", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem4 = toolsListWidget->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("ExerciseMainWindow", "Verteidiger+Puck", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem5 = toolsListWidget->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("ExerciseMainWindow", "Puck", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem6 = toolsListWidget->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("ExerciseMainWindow", "Pucks", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem7 = toolsListWidget->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("ExerciseMainWindow", "Pass", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem8 = toolsListWidget->item(8);
        ___qlistwidgetitem8->setText(QApplication::translate("ExerciseMainWindow", "Schlagschuss", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem9 = toolsListWidget->item(9);
        ___qlistwidgetitem9->setText(QApplication::translate("ExerciseMainWindow", "Schlenzer", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem10 = toolsListWidget->item(10);
        ___qlistwidgetitem10->setText(QApplication::translate("ExerciseMainWindow", "Schlange", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem11 = toolsListWidget->item(11);
        ___qlistwidgetitem11->setText(QApplication::translate("ExerciseMainWindow", "Schlange Stürmer", Q_NULLPTR));

        QListWidgetItem *___qlistwidgetitem12 = toolsListWidget->item(12);
        ___qlistwidgetitem12->setText(QApplication::translate("ExerciseMainWindow", "Schlange Verteidiger", Q_NULLPTR));








        toolsListWidget->setSortingEnabled(__sortingEnabled);

        toolsListWidgetDescriptorLabel->setText(QApplication::translate("ExerciseMainWindow", "Werkzeuge", Q_NULLPTR));

        const bool __sortingEnabled1 = timeslotsListWidget->isSortingEnabled();
        timeslotsListWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem19 = timeslotsListWidget->item(0);
        ___qlistwidgetitem19->setText(QApplication::translate("ExerciseMainWindow", "1", Q_NULLPTR));
        timeslotsListWidget->setSortingEnabled(__sortingEnabled1);

        timeslotsListWidgetDescriptorLabel->setText(QApplication::translate("ExerciseMainWindow", "Zeitschritte", Q_NULLPTR));
        timeslotFieldCanvasSelectComboBox->clear();
        timeslotFieldCanvasSelectComboBox->insertItems(0, QStringList()
         << QApplication::translate("ExerciseMainWindow", "Feld", Q_NULLPTR)
         << QApplication::translate("ExerciseMainWindow", "Feld quer", Q_NULLPTR)
         << QApplication::translate("ExerciseMainWindow", "Drittel", Q_NULLPTR)
         << QApplication::translate("ExerciseMainWindow", "Halbfeld", Q_NULLPTR)
         << QApplication::translate("ExerciseMainWindow", "Mitte", Q_NULLPTR)
        );
        timeslotsAddPushButton->setText(QApplication::translate("ExerciseMainWindow", "Hinzuf\303\274gen", Q_NULLPTR));
        timeslotsDeletePushButton->setText(QApplication::translate("ExerciseMainWindow", "L\303\266schen", Q_NULLPTR));
        toolColorSelectComboBox->clear();
        toolColorSelectComboBox->insertItems(0, QStringList()
         << QApplication::translate("ExerciseMainWindow", "Schwarz", Q_NULLPTR)
         << QApplication::translate("ExerciseMainWindow", "Rot", Q_NULLPTR)
         << QApplication::translate("ExerciseMainWindow", "Wei\303\237", Q_NULLPTR)
         << QApplication::translate("ExerciseMainWindow", "Gelb", Q_NULLPTR)
         << QApplication::translate("ExerciseMainWindow", "Gr\303\274n", Q_NULLPTR)
         << QApplication::translate("ExerciseMainWindow", "Blau", Q_NULLPTR)
        );
        animationShowPushButton->setText(QApplication::translate("ExerciseMainWindow", "Animation abspielen", Q_NULLPTR));
        animationLoopCheckbox->setText(QApplication::translate("ExerciseMainWindow", "Schleife", Q_NULLPTR));

        menuDatei->setTitle(QApplication::translate("ExerciseMainWindow", "Datei", Q_NULLPTR));
        menuBearbeiten->setTitle(QApplication::translate("ExerciseMainWindow", "Bearbeiten", Q_NULLPTR));
        menuInfo->setTitle(QApplication::translate("ExerciseMainWindow", "Hilfe", Q_NULLPTR));

        toolRotateRightPushButton->setText(QApplication::translate("ExerciseMainWindow", "-45°", Q_NULLPTR));
        toolRotateLeftPushButton->setText(QApplication::translate("ExerciseMainWindow", "+45°", Q_NULLPTR));
    } // retranslateUi







/**
 * @brief Ui_ExerciseMainWindow::buildTimeSlotsAnimations
 */
void Ui_ExerciseMainWindow::buildTimeSlotsAnimations(){
    if (builtScenes!=Q_NULLPTR){
        builtScenes->clear(); // potentially dagnerous
        delete builtScenes;
    }
    this->builtScenes = new SceneVector();
    this->builtSceneDurations = new std::vector<int>();

    int maxNrTotal = 1;
    std::list<TimeslotData*> *sortList= new std::list<TimeslotData*>();
    for (auto iter = globaldata->timeslots->begin(); iter != globaldata->timeslots->end(); ++iter){
        sortList->emplace_back((*iter).second);
        int t = (*iter).second->getMaxNumSteps();
        if(t>maxNrTotal){
            maxNrTotal = t;

        }
    }
    sortList->sort();



}; // buildTimeSlotsAnimations

/**
 * @brief Ui_ExerciseMainWindow::storeCurrentProgressInGif
 * @param speed
 * @param looped
 */
void Ui_ExerciseMainWindow::storeCurrentProgressInGif(){
    QGifImage tempGif (QSize(400, 400));

        QVector<QRgb> ctable;
        ctable << qRgb(255, 255, 255)
               << qRgb(0, 0, 0)
               << qRgb(255, 0, 0)
               << qRgb(0, 255, 0)
               << qRgb(0, 0, 255)
               << qRgb(255, 255, 0)
               << qRgb(0, 255, 255)
               << qRgb(255, 0, 255);

        tempGif.setGlobalColorTable(ctable, Qt::black);
        //tempGif.setDefaultTransparentColor(Qt::black);
        tempGif.setDefaultDelay(100);
        //![1]
        //![2]
 /*
        QImage image(100, 100, QImage::Format_RGB32);
        image.fill(QColor(Qt::black));
        QPainter p(&image);
        p.setPen(Qt::red);
        p.drawText(15, 15, "Qt");
        p.drawRect(20, 20, 60, 60);

        for (int i=0; i<10; ++i) {
            tempGif.addFrame(image, QPoint(i*20, i*20));
        }
        */
        //LDEBUG(builtTs->size());
        for (auto iter = builtScenes->begin(); iter !=builtScenes->end(); ++iter){
            //DEBUG(in gif loop);
            QGraphicsScene *s = *iter;
            QImage *p = new QImage();
            QPainter *painter = new QPainter (p);
            s->render(painter);

            QImage q = *p;
            q =  q.scaled(QSize(400, 400), Qt::KeepAspectRatio);
            tempGif.addFrame(q, (150-gifSpeedSlider->value())/4);
            painter->end();
            delete painter;

        }
        if(this->animationLoopCheckbox->isChecked()){
            tempGif.setLoopCount(0);
        }
        else{
            tempGif.setLoopCount(1);
        }
        // now store it temporarily
        QString path (PATH);
        tempGif.save(path);

}; //storeCUrrentProgressInGif

