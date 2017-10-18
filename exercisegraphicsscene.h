#ifndef EXERCISEGRAPHICSSCENE_H
#define EXERCISEGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QMouseEvent>

#include <iostream>
#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

class ExerciseGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ExerciseGraphicsScene(QObject* parent);
    ExerciseGraphicsScene();

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // EXERCISEGRAPHICSSCENE_H
