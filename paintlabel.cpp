#include "paintlabel.h"
#include "exerciseitem.h"
#include <QMouseEvent>
#include "exercisemainwindow.h"
#include <QPixmap>
#include <QPoint>

#include <iostream>
#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

#define STEP_WIDTH 6

#define OFFSET_POINT_LARGE(x) ((x += QPoint(20, 0)))
#define OFFSET_POINT_SMALL(x) ((x += QPoint(5, -5)))

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
 * @brief isPressEventTool
 * @param type
 * @return
 */
bool isPressEventTool(toolType type){
    LDEBUG(type);
    bool t = false;
    switch(type){
    case(puck):{
        t = true;
        break;
    }
    case(pucks):{
        break;
    }
    case(player):{
        t = true;
        break;
    }
    case(forward):{
        t = true;
        break;
    }
    case(defender):{
        t = true;
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
        break;
    }
    case(pass):{
        break;
    }

    case(stickhandling):{
        t = true;
        break;
    }
    case(slapshot):{
        t = true;
        break;
    }
    case(wristshot):{
        t = true;
        break;
    }
    case(runway):{
        break;
    }
    case(runway_with_puck):{

        break;
    }
    case(backwards):{
        break;
    }

    default:{
        break;
    }
    }
    return t;
}; // isPressEventTool

PaintLabel::PaintLabel(QWidget *parent): QLabel(parent){

}

void PaintLabel::mousePressEvent(QMouseEvent *event){
    DEBUG(label pressed);
    QPoint point = event->pos();
    if(mw->labelNotClickable){
        return;
    }
   toolType type =  mw->getCurrentSelectedToolType();
   if (isPressEventTool(type)){
       QImage image = mw->getCurrentSelectedCursor()->pixmap().toImage();
       toolType t = mw->getCurrentSelectedToolType();

       (this->draggedItem) = new ExerciseItem(&point, &image, t, true, new PointList());
       isDragged = true;
       mw->addExerciseItem(draggedItem);
       mw->repaintTimeSlot();
   }

   else{ // just single item (static in image)
       // ready; works
    QImage image = mw->getCurrentSelectedCursor()->pixmap().toImage();
    toolType t = mw->getCurrentSelectedToolType();
    ExerciseItem *item = new ExerciseItem(&point, &image, t, false, Q_NULLPTR);
    mw->addExerciseItem(item);
    mw->repaintTimeSlot();
   }

}

void PaintLabel::mouseReleaseEvent(QMouseEvent *event){
    DEBUG(label mouse released);
    dx = 0;
    dy = 0;
    draggedItem = Q_NULLPTR;
    movementPoints = Q_NULLPTR;
    isDragged = false;
}


void PaintLabel::mouseMoveEvent(QMouseEvent *event){

    if(isDragged){
        //LDEBUG(" mouse moved, x:" << event->pos().x() << " y:"<< event->pos().y());

        int x = event->pos().x();
        int y = event->pos().y();
        dx = x-dx;
        dy = y-dy;
        if(dx | dx){
            counter++;
        }
        if(counter==STEP_WIDTH){ // insert step in arrow
            DEBUG(counter 10);
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
            mw->repaintTimeSlot();
           // DEBUG(here);
        }

    }


}



