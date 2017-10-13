#include "exercisemainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ui_ExerciseMainWindow w;
    w.setupUi(&w, 1);
    w.show();

    return a.exec();
}
