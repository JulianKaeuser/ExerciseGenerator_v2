#include "exerciseitem.h"

/*
 *
 * class ExerciseItem
{
public:
    ExerciseItem(QPoint*, QImage*, toolType, QColor);
    ExerciseItem(const ExerciseItem&);
    ~ExerciseItem();
    QPoint point;
    QImage image;
    toolType type;
    QColor color;

private:

};
*/

/**
 * @brief ExerciseItem::ExerciseItem
 * @param point
 * @param image
 * @param type
 * @param color
 */
ExerciseItem::ExerciseItem(QPoint *point, QImage *image, toolType type, bool isDragged, PointList *list):
    point(*point),
    image(*image),
    type(type),
    isDragged(isDragged),
    movementPoints(list)
{

};

/**
 * @brief ExerciseItem::ExerciseItem
 * @param other
 */
ExerciseItem::ExerciseItem(const ExerciseItem &other){
    this->point = other.point;
    this->image = other.image;
    this->type = other.type;
    this->isDragged = other.isDragged;
    this->movementPoints = other.movementPoints;
};

/**
 * @brief ExerciseItem::~ExerciseItem
 */
ExerciseItem::~ExerciseItem(){

};



