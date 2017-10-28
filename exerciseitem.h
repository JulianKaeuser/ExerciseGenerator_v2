#ifndef EXERCISEITEM_H
#define EXERCISEITEM_H
#include <QPoint>
#include <QColor>
#include <vector>
#include <memory>
#include "tool.h"
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPointF>

#include "graphicsexerciseitem.h"


typedef std::vector<QPoint> PointList;

class ExerciseItem
{
public:
    ExerciseItem(QPoint point, Tool& tool, bool isNotSingle, PointList* movementPoints, GraphicsExerciseItem* sceneItem);
    ExerciseItem(const ExerciseItem&);
    ~ExerciseItem();
    QPoint point;
    GraphicsExerciseItem *gItem;
    Tool *tool;
    bool isNotSingle;
    PointList *movementPoints;
    QImage const &  getIcon();

    QPointF getMovementOffsetQPoint();

private:

};

#endif // EXERCISEITEM_H
