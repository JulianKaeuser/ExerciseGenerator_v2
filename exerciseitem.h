#ifndef EXERCISEITEM_H
#define EXERCISEITEM_H
#include <QPoint>
#include <QColor>
#include <vector>
#include <memory>
#include "tool.h"
#include <QGraphicsPixmapItem>
#include <QImage>


typedef std::vector<QPoint> PointList;

class ExerciseItem
{
public:
    ExerciseItem(QPoint, Tool&, bool, PointList*, QGraphicsPixmapItem*);
    ExerciseItem(const ExerciseItem&);
    ~ExerciseItem();
    QPoint point;
    QGraphicsPixmapItem *gItem;
    Tool *tool;
    bool isNotSingle;
    PointList *movementPoints;
    QImage const &  getIcon();

private:

};

#endif // EXERCISEITEM_H
