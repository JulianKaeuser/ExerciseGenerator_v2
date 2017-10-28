#ifndef MOVEMENTEXERCISEITEM_H
#define MOVEMENTEXERCISEITEM_H

#include <QRectF>
#include <QPainter>
#include <QGraphicsItem>
#include <QPointF>

#include "exercisemainwindow.h"
#include <vector>
#include <utility>


// forward declaration
class GraphicsExerciseItem;

typedef std::vector<QPointF> QPointFVector;


class MovementExerciseItem : public QGraphicsItem
{
public:
    MovementExerciseItem(GraphicsExerciseItem* parentGameObject, Ui_ExerciseMainWindow* mw, QPointF end);
    ~MovementExerciseItem();


    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QPointF getEndPoint();
    QPointFVector* getPoints();

    qreal getPathLength() const;
    void insertEquidistantGridPoints(int numStagesTotal);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

#ifdef MOUSE_EVENTS_MOVEMENTEXERCISEITEM__


    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
#endif //mouse stuff
    void setEnd(QPointF endPoint);

    Ui_ExerciseMainWindow *mw;


private:
    GraphicsExerciseItem* gameObject;
    QGraphicsScene* scene;
    QPointF end;
    QPointFVector *points;


    bool isLeftClicked = false;
    bool isRightClicked = false;
    QPointF initialClickPosition;


};

#endif // MOVEMENTEXERCISEITEM_H
