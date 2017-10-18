
#ifndef GRAPHICSEXERCISEITEM_H
#define GRAPHICSEXERCISEITEM_H

#include <QObject>
#include <QGraphicsItem>

// forward declaration
class Ui_ExerciseMainWindow;

//forward declaration
class ExerciseItem;



class GraphicsExerciseItem //: public QGraphicsItem
{

  //  Q_OBJECT
public:
    GraphicsExerciseItem();
    GraphicsExerciseItem(const GraphicsExerciseItem& other);
    Ui_ExerciseMainWindow *mw;
    QGraphicsScene *scene;
    ExerciseItem *eItem;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);


protected:


private:

};

#endif // GRAPHICSEXERCISEITEM_H

