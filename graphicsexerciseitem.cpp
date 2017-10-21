#include "graphicsexerciseitem.h"
#include "exercisemainwindow.h"
#include <QPainter>

#include <iostream>
#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

/**
 * @brief GraphicsExerciseItem::GraphicsExerciseItem
 */
GraphicsExerciseItem::GraphicsExerciseItem() : QGraphicsPixmapItem()
{

}// constructor

GraphicsExerciseItem::GraphicsExerciseItem(const QPixmap &pix, Ui_ExerciseMainWindow *mw) : QGraphicsPixmapItem(pix){
     QImage pix2 = pix.toImage();
    image = new QImage(pix2);
    scene = mw->getCurrentScene();

} // other constructor

/**
 * @brief GraphicsExerciseItem::GraphicsExerciseItem
 * @param parent
 */
GraphicsExerciseItem::GraphicsExerciseItem(QGraphicsItem *parent) : QGraphicsPixmapItem(parent){

} // parental constructor

/**
 * @brief GraphicsExerciseItem::GraphicsExerciseItem
 * @param other
 *
GraphicsExerciseItem::GraphicsExerciseItem(const GraphicsExerciseItem &other) : QGraphicsItem(other)
{
    this->eItem = other.eItem;
    this->mw = other.mw;
    this->scene = other.scene;

} // copy constructor
*/

/**
 * @brief GraphicsExerciseItem::mouseDoubleClickEvent
 * @param event
 */
void GraphicsExerciseItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    DEBUG(mosueCoubleClick);
    mw->setMovewayClicked(true);
} //mouseDoubleClickEvent



