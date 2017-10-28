#ifndef EXERCISEGRAPHICSSCENE_H
#define EXERCISEGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QMouseEvent>

//forward declaration
class GraphicsExerciseItem;

#include <vector>
#include <utility>

//forward declaration
class Ui_ExerciseMainWindow;

#include <iostream>
#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

class ExerciseGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ExerciseGraphicsScene(QObject* parent, Ui_ExerciseMainWindow* mw);
    ExerciseGraphicsScene(Ui_ExerciseMainWindow* mw);
    ExerciseGraphicsScene(const ExerciseGraphicsScene& other);
    ~ExerciseGraphicsScene();
    qreal getMaxPathLength();

    void addExerciseItem(GraphicsExerciseItem* item);
    void deleteExerciseItem(GraphicsExerciseItem* item);
    std::vector<GraphicsExerciseItem*> getExerciseItems() const;


    void mousePressEvent(QGraphicsSceneMouseEvent* event);



private:
    Ui_ExerciseMainWindow *mw;
    std::vector<GraphicsExerciseItem*> exerciseItems;
};

#endif // EXERCISEGRAPHICSSCENE_H
