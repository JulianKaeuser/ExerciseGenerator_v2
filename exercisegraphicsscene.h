#ifndef EXERCISEGRAPHICSSCENE_H
#define EXERCISEGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QMouseEvent>

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

    void mousePressEvent(QGraphicsSceneMouseEvent* event);



private:
    Ui_ExerciseMainWindow *mw;
};

#endif // EXERCISEGRAPHICSSCENE_H
