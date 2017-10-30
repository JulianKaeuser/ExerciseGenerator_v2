#include "exercisegraphicsscene.h"
#include "exercisemainwindow.h"
#include <QGraphicsSceneMouseEvent>
#include "graphicsexerciseitem.h"
#include "movementexerciseitem.h"

/**
 * @brief ExerciseGraphicsScene::ExerciseGraphicsScene
 * @param parent
 */
ExerciseGraphicsScene::ExerciseGraphicsScene(QObject *parent, Ui_ExerciseMainWindow* mw): QGraphicsScene(parent){
    this->mw = mw;
    this->exerciseItems = new std::vector<GraphicsExerciseItem*>();
}// constructor

/**
 * @brief ExerciseGraphicsScene::ExerciseGraphicsScene
 */
ExerciseGraphicsScene::ExerciseGraphicsScene(Ui_ExerciseMainWindow* mw) : QGraphicsScene()
{
    this->mw = mw;
    this->exerciseItems = new std::vector<GraphicsExerciseItem*>();
}// constructor

/**
 * @brief ExerciseGraphicsScene::ExerciseGraphicsScene
 * @param other
 *
ExerciseGraphicsScene::ExerciseGraphicsScene(const ExerciseGraphicsScene &other) {
    this->mw = other.mw;
    this->exerciseItems = new std::vector<GraphicsExerciseItem*>();
    for (auto iter = other.exerciseItems.begin(); iter!=other.exerciseItems.end(); ++iter){
        ExerciseItem* item = new ExerciseItem(&*((*iter)), this);
        this->exerciseItems.emplace_back(item);
    }

}// copy constructor
*/

/**
 * @brief ExerciseGraphicsScene::~ExerciseGraphicsScene
 */
ExerciseGraphicsScene::~ExerciseGraphicsScene(){

}//destructor


/**
 * @brief exerciseGraphicsScene::mousePressEvent
 * @param event
 */
void ExerciseGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(mw->isItemAddable()){
        DEBUG(mousePressEvent encountered);
        QPointF p = event->scenePos();
       // this->addItem(mw->generateCurrentGraphicsExerciseItem(p));
        if(mw->isTextItem()){
            DEBUG(text to set);
            QGraphicsTextItem *it = new QGraphicsTextItem(QString("Text"));
            it->setPos(p);
            this->addItem(it);

            it->setTextInteractionFlags(Qt::TextEditable);
            it->setFlag(QGraphicsItem::ItemIsMovable);
        }else{
            GraphicsExerciseItem *it = new GraphicsExerciseItem(mw->getCurrentSelectedToolType()->getCursor()->pixmap(), mw, mw->getCurrentSelectedToolType());
            //it->setFlag(Qt::ItemIsDragEnabled);

            it->setPos(p);
            this->addExerciseItem(it);
            it->setZValue(1);

            it->setPos(p);
            it->setFlag(QGraphicsItem::ItemIsMovable);

        }
        QGraphicsScene::mousePressEvent(event);
        mw->setItemAddable(false);
    }
    else{
        QGraphicsScene::mousePressEvent(event);
    }





}; // mousePressEvent

/**
 * @brief ExerciseGraphicsScene::getMaxPathLength
 * @return
 */
qreal ExerciseGraphicsScene::getMaxPathLength(){

    qreal maxLen = 0;
    for(auto iter = this->exerciseItems->begin(); iter!=this->exerciseItems->end(); ++iter){
        if((*iter)->hasMovement){
            qreal len = (*iter)->movementItem->getPathLength();
            if(len>maxLen){
               maxLen = len;
            }
        }
    }
}//getMaxPathLength

/**
 * @brief ExerciseGraphicsScene::addExerciseItem
 * @param item
 */
void ExerciseGraphicsScene::addExerciseItem(GraphicsExerciseItem *item){
    this->addItem(item);
    this->exerciseItems->emplace_back(item);
}//addExerciseItem

/**
 * @brief ExerciseGraphicsScene::deleteExerciseItem
 * @param item
 */
void ExerciseGraphicsScene::deleteExerciseItem(GraphicsExerciseItem *item){
    this->removeItem(item);
    for (auto iter = exerciseItems->begin(); iter!=exerciseItems->end(); ++iter){
        if((*iter)==item){
            this->exerciseItems->erase(iter);
            break;
            delete(item);
        }
    }

}// deleteExerciseItem

/**
 * @brief ExerciseGraphicsScene::deleteMovementItem
 * @param item
 */
void ExerciseGraphicsScene::deleteMovementItem(GraphicsExerciseItem* item){
    this->removeItem(item->movementItem);
    delete(item->movementItem);
    item->hasMovement = false;
}//deleteExerciseItem

/**
 * @brief ExerciseGraphicsScene::getExerciseItems
 * @return
 */
std::vector<GraphicsExerciseItem*>* ExerciseGraphicsScene::getExerciseItems() const{
    return this->exerciseItems;
}//getExerciseItems
