#ifndef PAINTLABEL_H
#define PAINTLABEL_H

#include <QObject>
#include <QLabel>
#include "exerciseitem.h"


// forward declaration
class TimeslotData;

class Ui_ExerciseMainWindow;

class PaintLabel : public QLabel
{
public:
    PaintLabel(QWidget*);
    Ui_ExerciseMainWindow *mw;


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    ExerciseItem *draggedItem;
    PointList *movementPoints;
    bool isDragged = false;
    bool isArrowed = false;
    int dx = 0;
    int dy = 0;
    int counter;
    TimeslotData* currentTs = Q_NULLPTR;


};

#endif // PAINTLABEL_H
