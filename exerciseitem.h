#ifndef EXERCISEITEM_H
#define EXERCISEITEM_H
#include <QPoint>
#include <QColor>
#include <vector>
#include <memory>
#include "toolutilities.h"

enum paintType {
    arrow = -1,
    single = 0,
    path = 1
};

typedef std::vector<QPoint> PointList;

typedef std::unique_ptr<QImage> QImagePointer;

class ExerciseItem
{
public:
    ExerciseItem(QPoint*,const QImage&, toolType, paintType, PointList*);
    ExerciseItem(const ExerciseItem&);
    ~ExerciseItem();
    QPoint point;
    QImagePointer icon;
    toolType type;
    paintType isDragged;  //(1 = dragged, 0 = single, -1 = arrow)
    PointList *movementPoints;

private:

};

#endif // EXERCISEITEM_H
