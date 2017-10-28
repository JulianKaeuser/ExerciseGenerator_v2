#include "graphicsexerciseitem.h"
#include "exercisemainwindow.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "movementexerciseitem.h"

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

GraphicsExerciseItem::GraphicsExerciseItem(const QPixmap &pix, Ui_ExerciseMainWindow *mw, Tool* tool) : QGraphicsPixmapItem(pix){
     QImage pix2 = pix.toImage();
    image = new QImage(pix2);
    scene = mw->getCurrentScene();
    this->mw = mw;
    this->tool = tool;

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
 */
GraphicsExerciseItem::GraphicsExerciseItem(const GraphicsExerciseItem &other, ExerciseGraphicsScene *scene)
{


    QImage pix2 = other.pixmap().toImage();
   image = new QImage(pix2);
   this->scene = scene;
   this->mw = other.mw;
   this->tool = tool;


} // copy constructor


/**
 * @brief GraphicsExerciseItem::mouseDoubleClickEvent
 * @param event
 */
void GraphicsExerciseItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    //DEBUG(mosueCoubleClick);
    //mw->setMovewayClicked(true);
    mw->graphicsView->viewport()->update();
} //mouseDoubleClickEvent

/**
 * @brief GraphicsExerciseItem::mousePressEvent
 * @param event
 */
void GraphicsExerciseItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Qt::MouseButton button = event->button();
    oldPoint = event->scenePos();

    if(button == Qt::RightButton){
        // do some arrow stuff
        DEBUG(right clicked);
        isRightClicked = true;
    }
    else if(button==Qt::LeftButton){
        isLeftClicked = true;
    }
    else{
        QGraphicsPixmapItem::mousePressEvent(event);
    }
    mw->graphicsView->viewport()->update();
} //mousePressEvent

/**
 * @brief GraphicsExerciseItem::mouseReleaseEvent
 * @param event
 */
void GraphicsExerciseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Qt::MouseButton button = event->button();
    if(button==Qt::MiddleButton){

        if(this->hasMovement){
            this->mw->getCurrentScene()->removeItem(this->movementItem);
            delete(this->movementItem);
            hasMovement = false;
        }
        scene->deleteExerciseItem(this);
    }
    else if(button==Qt::RightButton){
        if(hasMovement){
            if(movementItem!=Q_NULLPTR){
              scene->removeItem(movementItem);
              delete(movementItem);
            }
            movementItem = new MovementExerciseItem(this, mw, event->scenePos());
            scene->addItem(movementItem);
            movementItem->setZValue(0);


        }
        isRightClicked = false;
    }
    else if(isLeftClicked){
        /*
        if(hasMovement){
            if(movementItem!=Q_NULLPTR){
              scene->removeItem(movementItem);
              delete(movementItem);
            }
            movementItem = new MovementExerciseItem(this, mw, event->scenePos());
            scene->addItem(movementItem);

        }
        */
        isLeftClicked = false;
    }
    else {
        QGraphicsPixmapItem::mouseReleaseEvent(event);
    }
    //DEBUG(oldPoint set);
    oldPoint = event->scenePos();
    mw->graphicsView->viewport()->update();


}// mouseReleaseEvent


void GraphicsExerciseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(isRightClicked){
        if(tool->getDragType()==dragType::path || tool->getDragType()==dragType::arrow){
            hasMovement = true;
        }
    }
    if(isLeftClicked){
        if(hasMovement){
            hasMovement = false;
            scene->removeItem(movementItem);
            delete(movementItem);
            movementItem = Q_NULLPTR;
            /*
            QPointF p;
                p = movementItem->getEndPoint();
                scene->removeItem(movementItem);
              delete(movementItem);
                QPointF dPoint (event->scenePos().x()-oldPoint.x(), event->scenePos().y()-oldPoint.y());
            movementItem = new MovementExerciseItem(this, mw, p+=dPoint);
            scene->addItem(movementItem);
            */
        }
    }
        QGraphicsPixmapItem::mouseMoveEvent(event);
        oldPoint = event->scenePos();
        mw->graphicsView->viewport()->update();

} //mouseMoveEvent



