#ifndef PAINTLABEL_H
#define PAINTLABEL_H

#include <QObject>
#include <QLabel>
#include "exerciseitem.h"

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
    int dx = 0;
    int dy = 0;
    int counter;


};

#endif // PAINTLABEL_H