#include "paintlabel.h"
#include "exerciseitem.h"
#include <QMouseEvent>
#include "exercisemainwindow.h"
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QPen>
#include "timeslotdata.h"

#include <iostream>
#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

#define STEP_WIDTH 2

#define OFFSET_POINT_LARGE(x) ((x += QPoint(20, 0)))
#define OFFSET_POINT_SMALL(x) ((x += QPoint(5, -5)))

#define MAX(x,y) ((x<y) ? y : x)
#define MIN(x,y) ((x<y) ? x : y)

#define ABS(x) if (x<0){ x = -x;}

/*
 * enum toolType{
    player = 0,
    forward = 1,
    defender = 2,
    group = 3,
    forward_group = 4,
    defender_group = 5,
    puck = 6,
    pucks = 7,
    pass = 8,
    runway = 9,
    runway_with_puck = 10,
    stickhandling = 11,
    slapshot = 12,
    wristshot = 13,
    backwards = 14,
    turn = 15,
    line = 16,
    forward_line = 17,
    defender_line = 18
};
*/

/**
  Returns the type of action for this tool.
  1 = draggable
  -1 =arrow event
  0 = single
 * @brief isPressEventTool
 * @param type
 * @return
 */
paintType isPressEventTool(toolType type){
    //LDEBUG("isPressEventTool: " <<type);
    // return -1 if arrow type, 0 if nothing, 1 if drag
    int t = 0;
    switch(type){
    case(puck):{
        t = 1;
        break;
    }
    case(pucks):{
        break;
    }
    case(player):{
        t = 1;
        break;
    }
    case(forward):{
        t = 1;
        break;
    }
    case(defender):{
        t = 1;
        break;
    }
    case(group):{
        break;
    }
    case(defender_group):{
        break;
    }
    case(forward_group):{
        break;
    }
    case(line):{
        break;
    }
    case(forward_line):{
        break;
    }
    case(defender_line):{
        break;
    }
        //non-elemnt types
    case(turn):{
        t = -1;
        break;
    }
    case(pass):{
        t = -1;
        break;
    }

    case(stickhandling):{
        t = 1;
        break;
    }
    case(slapshot):{
        t = -1;
        break;
    }
    case(wristshot):{
        t = -1;
        break;
    }
    case(runway):{
        break;
    }
    case(runway_with_puck):{

        break;
    }
    case(backwards):{
        t = -1;
        break;
    }

    default:{
        break;
    }
    }
    return static_cast<paintType> (t);
}; // isPressEventTool

PaintLabel::PaintLabel(QWidget *parent): QLabel(parent){

}

void PaintLabel::mousePressEvent(QMouseEvent *event){
  //  DEBUG(mousePressVenet:label pressed);
    QPoint point = event->pos();
    if(mw->labelNotClickable){
        return;
    }

   QImage icon = mw->getCurrentSelectedCursor()->pixmap().toImage();
   toolType type =  mw->getCurrentSelectedToolType();

   if (isPressEventTool(type)==paintType::path){
        // draw path/add path items
       (this->draggedItem) = new ExerciseItem(point, icon, type, paintType::path, new PointList());
       isDragged = true;
       isArrowed = false;
       mw->addExerciseItem(draggedItem);
       mw->repaintTimeSlot();
   }
   if(isPressEventTool(type)==paintType::arrow){
       // do stuff for arrows here
     //  DEBUG(mousPressEvent: arrow type clicked);
       isDragged = false;
       isArrowed = true;
       this->draggedItem = new ExerciseItem(point, icon, type, paintType::path, new PointList());
       mw->addExerciseItem(draggedItem);
      // currentTs = (*(mw->globaldata->timeslots))[mw->currentSelectedTimeslot];
       mw->repaintTimeSlot();


   }

   if(isPressEventTool(type)==paintType::single){
       // just single item (static in image)
       // ready; works
        ExerciseItem *item = new ExerciseItem(point, icon, type, paintType::single, Q_NULLPTR);
        mw->addExerciseItem(item);
        mw->repaintTimeSlot();
   }

} // mousePressEvent

void PaintLabel::mouseReleaseEvent(QMouseEvent *event){
    //DEBUG(label mouse released);
    event->accept();
    dx = 0;
    dy = 0;
    draggedItem = Q_NULLPTR;
    movementPoints = Q_NULLPTR;
    isDragged = false;


    if(isArrowed){
        mw->repaintTimeSlot();
    }
    isArrowed = false;
}


void PaintLabel::mouseMoveEvent(QMouseEvent *event){
    //DEBUG(mouseMove);

    if(isDragged){

        int x = event->pos().x();
        int y = event->pos().y();
        dx = x-dx;
        dy = y-dy;
        if(dx | dx){
            counter++;
        }
        if(counter==STEP_WIDTH){ // insert step in arrow
          // DEBUG(counter 10);
            counter =0;
            dx = 0;
            dy = 0;
            QPoint point = event->pos();

            if(mw->getCurrentSelectedToolType()==toolType::puck){
                OFFSET_POINT_SMALL(point);
            }
            else{
                OFFSET_POINT_LARGE(point);
            }

            draggedItem->movementPoints->emplace_back(point);
            //DEBUG(inMoveEvent);
            mw->repaintTimeSlot();
            //DEBUG(inMoveEvent2);
           // DEBUG(here);
        }

    }
    // do arrow intermediate stuff
     if (isArrowed){
        // insert step in arrow
            QPoint point = event->pos();

            delete draggedItem->movementPoints;
            draggedItem->movementPoints = new PointList();
            draggedItem->movementPoints->emplace_back(point);
           // mw->repaintTimeSlot();
           // DEBUG(here);


    } // isArrowed
}



