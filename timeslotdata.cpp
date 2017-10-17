#include "timeslotdata.h"
#include <QPainter>
#include <iostream>

#define OFFSET_POINT_LARGE(x) ((x += QPoint(20, 0)))
#define OFFSET_POINT_SMALL(x) ((x += QPoint(5, 0)))

#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

/**
 * @brief interPolatePoints
 * @param a
 * @param b
 * @return
 */
QPoint* interPolatePoints(QPoint &a, QPoint &b){

    int x = b.x() + a.x();
    int y = b.y() + a.y();
    x = x/2;
    y = y/2;
    QPoint *p = new QPoint(x, y);


    return p;
}; // interpolatePoints

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
TimeslotData::TimeslotData(int number, int listIndex, QListWidgetItem* item, QImage *image, QImage *canvas, canvasType ct, QGraphicsScene* scene):
    number(number),
    listIndex(listIndex),
    item(item),
    image(image),
    canvas(canvas),
    scene(scene),
    ct(ct)
{
    ExerciseItemVector *ex = new ExerciseItemVector();
    this->objects = *ex;
}; // usual constructor

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
    this->canvas = new QImage(*other.canvas);
    this->image =  new QImage(*other.image);
    this->ct = other.ct;
    this->item = other.item; // must be the same, not copy; else, it will never work with listWidget
    this->objects = *(new ExerciseItemVector(other.objects));
    this->scene = other.scene;
}; //copy constructor

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
    if(this->scene != other.scene) return false;
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

/**
 * @brief TimeslotData::getMaxNumSteps
 * @return
 */
int TimeslotData::getMaxNumSteps(){
    int max = 1;

    for (auto iter = objects.begin(); iter !=objects.end(); ++iter){
        if((*iter)->movementPoints !=Q_NULLPTR){
            int curr = (*iter)->movementPoints->size();
            if(curr >=max) max = curr;
        }
    }
    return max;
};//getMaxNumSteps;


/**
 * @brief TimeslotData::insertBuiltTimesteps
 * @param tsBuffer
 * @param tsDurationsBuffer
 * @param speed
 * @param loop
 */
void TimeslotData::insertBuiltTimesteps(SceneVector *sceneBuffer, std::vector<int> *tsDurationsBuffer,int totalMaxPoints){

    /*
     * How to:
     * 1. interpolate all points and add missing ones until every item has the maxNum of movement points
     * 2. paint every resulting point as a separate QImage
     *
     */


    computeInterpolation(totalMaxPoints);
    /*
    DEBUG(interpolated);
    for (auto iter = objects.begin(); iter!=objects.end(); ++iter){
        LDEBUG("new item, type: " <<(*iter)->type);
        int ii = 1;
        for (auto mIter = (*iter)->movementPoints->begin(); mIter != (*iter)->movementPoints->end(); ++mIter){
            LDEBUG("next point: " << ii << " x" <<(*mIter).x() << " y" << (*mIter).y());
            ii++;
        }
    }
    */

    /*
    for (int ii = 0; ii<totalMaxPoints+1; ii++){
        tsBuffer->emplace_back(paintRawTimeSlot(*this, ii, label));
        tsDurationsBuffer->emplace_back(speed);
    }
*/


}; //insertBuiltTimesteps

/**
 * @brief TimeslotData::computeInterpolation
 */
void TimeslotData::computeInterpolation(int totalMaxPoints){
        int nrTotal = totalMaxPoints;
        //DEBUG(trying interpolation);
        // for each exerciseItem, construct path according to total number
        /*
        for (auto iter = objects.begin(); iter!=objects.end(); ++iter){

            if ((*iter)->isDragged==paintType::single){
                PointList *list = new PointList();
                (*iter)->movementPoints = list;
                for (int ii = 0; ii<nrTotal; ii++){
                    QPoint *point = new QPoint((*iter)->point.x(), (*iter)->point.y());
                    list->emplace_back(*point);
                }
            }
            if ((*iter)->isDragged!=paintType::single && (*iter)->movementPoints->empty()){
                PointList *list = new PointList();
                (*iter)->movementPoints = list;
                for (int ii = 0; ii<nrTotal; ii++){
                    QPoint *point = new QPoint((*iter)->point.x(), (*iter)->point.y());
                    list->emplace_back(*point);
                }
            }

            // if the item is not single AND
            // as long as there are less than nrTotal points on the line
            auto mIter = ((*iter)->movementPoints->begin());
            QPoint currentA = ((*iter)->point);
            QPoint currentB = *mIter;

            while( (*iter)->movementPoints->size()<nrTotal){
                //interpolate and insert
                QPoint *interPoint = interPolatePoints(currentA, currentB);
               mIter =  (*iter)->movementPoints->insert(mIter, *interPoint);

                currentA = currentB;
                mIter++;
                mIter++;
                if(mIter != (*iter)->movementPoints->end()){
                    currentB= (*mIter);
                } else {
                   currentA = ((*iter)->point);
                   currentB = *((*iter)->movementPoints->begin());
                   mIter = (*iter)->movementPoints->begin();
                }

            }// while

        }// for each exercise item
        */
} // computeInterpolation

/**
   paints the items of this TimeSlotData into the canvas. Requires that for every item, the point must be there
 * @brief paintRawTimeSlot
 * @param ts
 */
QImage* paintRawTimeSlot(const TimeslotData& tsb, int index){

    TimeslotData *tsp = new TimeslotData (tsb);
    TimeslotData ts = *tsp;

   /* canvasType type = static_cast<canvasType>(ts.ct);

    QImage *im =  ( new QImage(":/imageSources/fullFieldCanvas.png"));
       switch(type){
            case(full):{
                im = new QImage(":/imageSources/fullFieldCanvas.png");

                break;
            }
            case(full90):{
                im= new QImage(":/imageSources/fullField90Canvas.png");
                break;
            }
            case(third):{
                im= new QImage(":/imageSources/thirdFieldCanvas.png");
                break;
            }
            case(half):{
                im= new QImage(":/imageSources/halfFieldCanvas.png");
                break;
            }
            case(middle):{
                im= new QImage(":/imageSources/middleFieldCanvas.png");
                break;
            }
            default:
                break;
            }
    QImage *imageP = im;


    // for each object, paint it on the canvas
    for (auto iter = ts.objects.begin(); iter!=ts.objects.end(); ++iter){

        QPainter painter (imageP);
        QPoint point;
        if (index !=0){
            int indShifted = index-1;
            point = (*iter)->movementPoints->at(indShifted);
        } else {
            point = (*iter)->point;
        }
        QPoint *pointMapped = getMappedPoint(&point, imageP, label);
        QImage exerciseItemIcon = *((*iter)->icon);

              if((*iter)->type==toolType::puck){
                  OFFSET_POINT_SMALL(*pointMapped);
              }
              else{
                  OFFSET_POINT_LARGE(*pointMapped);
              }
              painter.setBackground(QBrush(Qt::white));
        painter.drawImage(*pointMapped, exerciseItemIcon);
        painter.end();
    }// iter over all exerciseItems
   return imageP;
   */

} //paintRawTS



