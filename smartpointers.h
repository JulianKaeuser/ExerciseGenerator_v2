#ifndef SMARTPOINTERS_H
#define SMARTPOINTERS_H

#include <QListWidgetItem>
#include <QString>
#include <QPixmap>
#include <QImage>

#include <memory>

// forward declaration of TimeslotData;
class TimeslotData;


typedef std::shared_ptr<QPixmap> QPixmapPointer;

typedef std::shared_ptr<TimeslotData> TimeslotDataPointer;

typedef std::shared_ptr<QListWidgetItem> QListWidgetItemPointer;

typedef std::shared_ptr<QString> QStringPointer;


/*
QImagePointer getQImagePointer(QImage*);
QPixmapPointer getQPixmapPointer(QPixmap*);

TimeslotDataPointer getTimeslotDataPointer(TimeslotData*);

QListWidgetItemPointer getQListWidgetItemPointer (QListWidgetItem*);

QStringPointer getQStringPointer(QString*);
*/

#endif // SMARTPOINTERS_H
