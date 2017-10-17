#include "exerciseitem.h"
#include <memory>

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
ExerciseItem::ExerciseItem(QPoint point, const QImage& icon, toolType type, paintType isDragged, PointList *list):
    point(point),
    icon(std::make_unique<QImage>(icon)),
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
    this->icon = std::make_unique<QImage>(*other.icon);
    this->type = other.type;
    this->isDragged = other.isDragged;
    this->movementPoints = other.movementPoints;
};

/**
 * @brief ExerciseItem::~ExerciseItem
 */
ExerciseItem::~ExerciseItem(){

};



