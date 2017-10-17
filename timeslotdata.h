#ifndef TIMESLOTDATA_H
#define TIMESLOTDATA_H
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGraphicsScene>


#include <memory>
#include <vector>
#include "exerciseitem.h"



class TimeslotData;


/*
 * fieldCanvasTypes:
 * 0 = full
 * 1 = full90
 * 2 = third
 * 3 = half
 * 4 = middle
 */

typedef std::vector<ExerciseItem*> ExerciseItemVector;

#ifndef __TIMESLOTIMAGEVECTOR_T
#define __TIMESLOTIMAGEVECTOR_T
typedef std::vector<QImage*> TimeslotImageVector;
typedef std::vector<QGraphicsScene*> SceneVector;
#endif
 enum canvasType {
    full = 0,
    full90 = 1,
    third = 2,
    half = 3,
    middle = 4,
    unused = 1000

};

 class TimeslotData{
 public:
     int number;
     int listIndex;
     QListWidgetItem  *item;
     QImage *image;
     QImage *canvas;
     QGraphicsScene *scene;
     canvasType ct;
     ExerciseItemVector objects;
     TimeslotData(int, int, QListWidgetItem*, QImage*, QImage*, canvasType, QGraphicsScene*);
     TimeslotData(const TimeslotData&);
     ~TimeslotData();
     bool operator>(const TimeslotData&);
     bool operator<(const TimeslotData&);
     bool operator==(const TimeslotData&);
     bool operator>=(const TimeslotData&);
     bool operator<=(const TimeslotData&);
     bool operator!=(const TimeslotData&);

     int getMaxNumSteps();
     void insertBuiltTimesteps(SceneVector*, std::vector<int>*,int);


     void computeInterpolation(int);
    // QImage* paintRawTimeSlot(const TimeslotData& ,int, PaintLabel*);

 private:




 };



#endif // TIMESLOTDATA_H
