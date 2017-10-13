#ifndef GLOBALDATA_H
#define GLOBALDATA_H
#include <vector>
#include <QString>
#include "timeslotdata.h"
#include "smartpointers.h"


typedef struct {
    int id;
    QStringPointer path;
    std::map<QListWidgetItem* , TimeslotData*> *timeslots;
} globalData;

#endif // GLOBALDATA_H
