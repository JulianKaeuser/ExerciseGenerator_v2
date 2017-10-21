#include "exercisegraphicsscene.h"
#include "exercisemainwindow.h"
#include <QGraphicsSceneMouseEvent>
#include "graphicsexerciseitem.h"

/**
 * @brief ExerciseGraphicsScene::ExerciseGraphicsScene
 * @param parent
 */
ExerciseGraphicsScene::ExerciseGraphicsScene(QObject *parent, Ui_ExerciseMainWindow* mw): QGraphicsScene(parent){
    this->mw = mw;
}// constructor

/**
 * @brief ExerciseGraphicsScene::ExerciseGraphicsScene
 */
ExerciseGraphicsScene::ExerciseGraphicsScene(Ui_ExerciseMainWindow* mw) : QGraphicsScene()
{
    this->mw = mw;
}// constructor


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
            GraphicsExerciseItem *it = new GraphicsExerciseItem(mw->getCurrentSelectedToolType()->getCursor()->pixmap(), mw);
            //it->setFlag(Qt::ItemIsDragEnabled);

            it->setPos(p);
            this->addItem(it);

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
