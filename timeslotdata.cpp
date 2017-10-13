#include "timeslotdata.h"

/*
class TimeslotData{
public:
    int number;
    int listIndex;
    QListWidgetItem *item;
    QImage *image;
    QImage *canvas;
    canvasType ct;
    TimeslotData(int, int, QListWidgetItem*, QImage*, QImage*, canvasType);
    bool operator>(const TimeslotData&);
    bool operator<(const TimeslotData&);
    bool operator==(const TimeslotData&);
    bool operator>=(const TimeslotData&);
    bool operator<=(const TimeslotData&);
    bool operator!=(const TimeslotData&);
private:

    ~TimeslotData();
    TimeslotData(const TimeslotData&);

}
*/

/**
 * @brief TimeslotData::TimeslotData
 * @param number
 * @param listIndex
 * @param item
 * @param image
 * @param canvas
 * @param ct
 */
TimeslotData::TimeslotData(int number, int listIndex, QListWidgetItem* item, QImage *image, QImage *canvas, canvasType ct):
    number(number),
    listIndex(listIndex),
    item(item),
    image(image),
    canvas(canvas),
    ct(ct)
{
    ExerciseItemVector *ex = new ExerciseItemVector();
    this->objects = *ex;
}

/**
 * @brief TimeslotData::~TimeslotData
 */
TimeslotData::~TimeslotData(){
}

/**
 * @brief TimeslotData::TimeslotData
 * @param other
 */
TimeslotData::TimeslotData(const TimeslotData &other){
    this->number = other.number;
    this->listIndex = other.listIndex;
    this->canvas = other.canvas;
    this->image = other.image;
    this->ct = other.ct;
    this->item = other.item;
    this->objects = other.objects;
}

/**
 * @brief TimeslotData::operator !=
 * @param other
 * @return
 */
bool TimeslotData::operator !=(const TimeslotData &other){
    if (this->canvas != other.canvas) return false;
    if(this->ct != other.ct) return false;
    if(this->item != other.item) return false;
    if(this->listIndex != other.listIndex) return false;
    if(this->image != other.image) return false;
    if(this->number != other.number) return false;
    return true;
}

/**
 * @brief TimeslotData::operator >
 * @param other
 * @return
 */
bool TimeslotData::operator>(const TimeslotData &other){
    if (this->number>other.number) return true;
    return false;
}

/**
 * @brief TimeslotData::operator <
 * @param other
 * @return
 */
bool TimeslotData::operator <(const TimeslotData &other){
    if(this->number<other.number) return true;
    return false;
}

/**
 * @brief TimeslotData::operator <=
 * @param other
 * @return
 */
bool TimeslotData::operator <=(const TimeslotData &other){
    if(this->number<=other.number) return true;
    return false;
}

/**
 * @brief TimeslotData::operator >=
 * @param other
 * @return
 */
bool TimeslotData::operator >=(const TimeslotData &other){
    if(this->number>=other.number) return true;
    return false;
}

/**
 * @brief TimeslotData::operator ==
 * @param other
 * @return
 */
bool TimeslotData::operator==(const TimeslotData &other){
    return !( *this!=other);
}




