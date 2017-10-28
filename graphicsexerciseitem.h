
#ifndef GRAPHICSEXERCISEITEM_H
#define GRAPHICSEXERCISEITEM_H

//#include <QObject>
#include <QGraphicsItem>
#include "tool.h"


// forward declaration
class Ui_ExerciseMainWindow;

//forward declaration
class ExerciseItem;

//forward declaration
class MovementExerciseItem;

//forward declaration
class ExerciseGraphicsScene;


class GraphicsExerciseItem : public QGraphicsPixmapItem
{


public:
    GraphicsExerciseItem();
    GraphicsExerciseItem(QGraphicsItem* parent);
    GraphicsExerciseItem(const QPixmap& pix, Ui_ExerciseMainWindow* mw, Tool* tool);
    GraphicsExerciseItem(const GraphicsExerciseItem& other, ExerciseGraphicsScene* scene);
    Ui_ExerciseMainWindow *mw;
    ExerciseGraphicsScene *scene;
    ExerciseItem *eItem;
    QImage *image;
    bool hasMovement = false;
    Tool* tool = Q_NULLPTR;
    MovementExerciseItem* movementItem = Q_NULLPTR;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);





protected:


private:
    bool isRightClicked = false;
    bool isLeftClicked = false;
    QPointF oldPoint;

};

#endif // GRAPHICSEXERCISEITEM_H

