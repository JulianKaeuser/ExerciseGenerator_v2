#ifndef EXERCISEITEM_H
#define EXERCISEITEM_H
#include <QPoint>
#include <QColor>
#include <vector>

#include "toolutilities.h"

typedef std::vector<QPoint> PointList;

class ExerciseItem
{
public:
    ExerciseItem(QPoint*, QImage*, toolType, bool, PointList*);
    ExerciseItem(const ExerciseItem&);
    ~ExerciseItem();
    QPoint point;
    QImage image;
    toolType type;
    bool isDragged;
    PointList *movementPoints;

private:

};

#endif // EXERCISEITEM_H
