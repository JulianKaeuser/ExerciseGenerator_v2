#include "exercisegraphicsscene.h"

/**
 * @brief ExerciseGraphicsScene::ExerciseGraphicsScene
 * @param parent
 */
ExerciseGraphicsScene::ExerciseGraphicsScene(QObject *parent): QGraphicsScene(parent){

}//copy constructor

/**
 * @brief ExerciseGraphicsScene::ExerciseGraphicsScene
 */
ExerciseGraphicsScene::ExerciseGraphicsScene() : QGraphicsScene()
{

}// constructor


/**
 * @brief exerciseGraphicsScene::mousePressEvent
 * @param event
 */
void ExerciseGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    DEBUG(mousePressEvent encountered);
    QGraphicsScene::mousePressEvent(event);
}; // mousePressEvent
