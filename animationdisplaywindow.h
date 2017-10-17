#ifndef ANIMATIONDISPLAYWINDOW_H
#define ANIMATIONDISPLAYWINDOW_H


#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QLabel>

// forward declaration
class Ui_ExerciseMainWindow;



class AnimationDisplayWindow : public QMainWindow
{
public:
    AnimationDisplayWindow(int, bool, QString);
    ~AnimationDisplayWindow();
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(Ui_ExerciseMainWindow *MainWindow, char *argv0, int percentSpeed, bool isLooped);

    void retranslateUi(QMainWindow *MainWindow);

private:
    AnimationDisplayWindow(const AnimationDisplayWindow&);
    QMovie *movie = Q_NULLPTR;
    QLabel *processLabel = Q_NULLPTR;
};




#endif // ANIMATIONDISPLAYWINDOW_H
