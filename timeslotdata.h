#ifndef TIMESLOTDATA_H
#define TIMESLOTDATA_H
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>


#include <memory>
#include <vector>
#include "exerciseitem.h"
//#include "smartpointers.h"


/*
 * fieldCanvasTypes:
 * 0 = full
 * 1 = full90
 * 2 = third
 * 3 = half
 * 4 = middle
 */

typedef std::vector<ExerciseItem*> ExerciseItemVector;
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
     canvasType ct;
     ExerciseItemVector objects;
     TimeslotData(int, int, QListWidgetItem*, QImage*, QImage*, canvasType);
     TimeslotData(const TimeslotData&);
     ~TimeslotData();
     bool operator>(const TimeslotData&);
     bool operator<(const TimeslotData&);
     bool operator==(const TimeslotData&);
     bool operator>=(const TimeslotData&);
     bool operator<=(const TimeslotData&);
     bool operator!=(const TimeslotData&);
 private:




 };



#endif // TIMESLOTDATA_H
