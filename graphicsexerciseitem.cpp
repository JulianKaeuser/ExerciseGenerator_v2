#include "graphicsexerciseitem.h"

/**
 * @brief GraphicsExerciseItem::GraphicsExerciseItem
 */
GraphicsExerciseItem::GraphicsExerciseItem()
{

}// constructor

/**
 * @brief GraphicsExerciseItem::GraphicsExerciseItem
 * @param other
 */
GraphicsExerciseItem::GraphicsExerciseItem(const GraphicsExerciseItem &other)
{
    this->eItem = other.eItem;
    this->mw = other.mw;
    this->scene = other.scene;

} // copy constructor


