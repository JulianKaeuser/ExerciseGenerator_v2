#include "exerciseitem.h"
#include <memory>
#include <QImage>

#include <iostream>
#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

/**
 * @brief ExerciseItem::ExerciseItem
 * @param point
 * @param image
 * @param type
 * @param color
 */
ExerciseItem::ExerciseItem(QPoint point, Tool &tool,bool isNotSingle, PointList *list, GraphicsExerciseItem *pixItem):
    point(point),
    tool(&tool),
    isNotSingle(isNotSingle),
    movementPoints(list),
    gItem(pixItem)
{

}; //usual constructor

/**
 * @brief ExerciseItem::ExerciseItem
 * @param other
 */
ExerciseItem::ExerciseItem(const ExerciseItem &other){
    QPoint *p = new QPoint(other.point);
    this->point = *p;
    this->tool = new Tool(*other.tool);
    this->isNotSingle = other.isNotSingle;
    PointList *pL = new PointList(*other.movementPoints);
    this->movementPoints = pL;
    this->gItem = new GraphicsExerciseItem(*other.gItem);
}; // copy constructor

/**
 * @brief ExerciseItem::~ExerciseItem
 */
ExerciseItem::~ExerciseItem(){
    delete(tool);
    delete(movementPoints);
    delete(gItem);
}; //destructor

/**
 * @brief ExerciseItem::getIcon
 * @return
 */
QImage const &   ExerciseItem::getIcon(){
    return this->tool->getCursor()->pixmap().toImage();
}// getIcon
