#include "smartpointers.h"

#include "timeslotdata.h"

#include <iostream>


#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

/*
QImagePointer getQImagePointer(QImage *ptr){
     QImagePointer q = std::make_shared<QImage>();
     DEBUG(called);
     q.reset();
     DEBUG(t);
     *q = *ptr;
     return q;

    //return std::make_shared<QImage> (ptr);
}

QPixmap* getQPixmapPointer(QPixmap *ptr){
    QPixmapPointer q;// =  std::make_shared<QPixmap>();
    q.reset();
    *q = *ptr;
    return q;
}

TimeslotData* getTimeslotDataPointer(TimeslotData *ptr){
    TimeslotDataPointer q;// =  std::make_shared<TimeslotData>();
    q.reset();
    *q = *ptr;
    return q;
}

QListWidgetItem* getQListWidgetItemPointer (QListWidgetItem *ptr){
    QListWidgetItemPointer q;// =  std::make_shared<QListWidgetItem> ();
    q.reset();
    *q = *ptr;
    return q;
}

QStringPointer getQStringPointer(QString *ptr){
    QStringPointer q;// =  std::make_shared<QString> ();
    q.reset();
    *q = *ptr;
    return q;
}
*/
