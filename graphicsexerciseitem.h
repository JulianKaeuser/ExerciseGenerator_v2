
#ifndef GRAPHICSEXERCISEITEM_H
#define GRAPHICSEXERCISEITEM_H

//#include <QObject>
#include <QGraphicsItem>

// forward declaration
class Ui_ExerciseMainWindow;

//forward declaration
class ExerciseItem;



class GraphicsExerciseItem : public QGraphicsPixmapItem
{


public:
    GraphicsExerciseItem();
    GraphicsExerciseItem(QGraphicsItem* parent);
    GraphicsExerciseItem(const QPixmap& pix, Ui_ExerciseMainWindow* mw);
    GraphicsExerciseItem(const GraphicsExerciseItem& other) = delete;
    Ui_ExerciseMainWindow *mw;
    QGraphicsScene *scene;
    ExerciseItem *eItem;
    QImage *image;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);





protected:


private:

};

#endif // GRAPHICSEXERCISEITEM_H

