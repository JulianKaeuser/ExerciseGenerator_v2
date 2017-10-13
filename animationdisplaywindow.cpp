#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QMovie>

//#include "filepathhelper.h"
//#include "gamedefines.h"
#include "animationdisplaywindow.h"
#include "ui_exercisemainwindow.h"
#include "smartpointers.h"


// constructor
 AnimationDisplayWindow::AnimationDisplayWindow(int speed, bool loop, QString path){
    int percentSpeed = speed;
    this->resize(700, 600);
    movie = new QMovie(path);
    processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    processLabel->resize(500, 500);

    movie->start();
    movie->setSpeed(percentSpeed);
}

 // destructor (public)
 AnimationDisplayWindow::~AnimationDisplayWindow(){
     if(movie!=Q_NULLPTR){
         free(movie);
        }
     if(processLabel!=Q_NULLPTR){
        free(processLabel);
     }
 }

 // private copy constructor
 AnimationDisplayWindow::AnimationDisplayWindow(const AnimationDisplayWindow &other){
     // permitted anyway
 }


 // setupUi Function
    void AnimationDisplayWindow::setupUi(Ui_ExerciseMainWindow *MainWindow, char* argv0, int percentSpeed, bool isLooped)
    {
        /*
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1500, 1200);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        this->argv0 = argv0;

        QString basePath(executable_path(argv0).c_str());
        basePath.chop(18);
        basePath.append(TEMP_ANIMATION_STORAGE);
        *
        MainWindow->resize(1500, 1200);
        movie = new QMovie("null");
        processLabel = new QLabel(this);
        processLabel->setMovie(movie);
        processLabel->resize(500, 500);

        movie->start();
        movie->setSpeed(percentSpeed);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
*/
    } // setupUi

    void AnimationDisplayWindow::retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
    } // retranslateUi



