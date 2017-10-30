#include "movementexerciseitem.h"

#include <math.h>
#include <QGraphicsSceneMouseEvent>

#include <iostream>
#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

/**
 * @brief getDirectedOffset
 * @param begin
 * @param end
 * @return
 */
QPointF paintMovementArrowHead(QPointF begin, QPointF end, QPainter *painter){

    // not finished by now (whole method)


    qreal arrowAngle = 2*M_PI/3;
    qreal arrowLen = 15;
    qreal xA = begin.x();
    qreal xB = end.x();
    qreal yA = begin.y();
    qreal yB = end.y();

    qreal dX = xB-xA;
    qreal dY = yB-yA;

    qreal vectorAngle = M_PI/2;
    if(dX==0 && dY>0){
        vectorAngle = - M_PI/2;
    }
    else if(dX==0 &&dY>=0){
        // nothing to do here
    }
    else{
        vectorAngle = atan(dY/dX);
    }
    //left
    qreal myLeft = M_PI/2 - arrowAngle-M_PI +vectorAngle;
    qreal deltaYLeft = arrowLen*cos(myLeft);
    qreal deltaXLeft = arrowLen*sin(myLeft);
    QPointF leftArrowEnd(end.x()+deltaXLeft, end.y()+deltaYLeft);
    //painter->drawLine(end, leftArrowEnd);

    //right
    qreal myRight = M_PI/2 -vectorAngle - arrowAngle -M_PI;
    qreal deltaYRight = arrowLen*sin(myRight);
    qreal deltaXRight = arrowLen*cos(myRight);
    QPointF rightArrowEnd(end.x()+deltaXRight, end.y()+deltaYRight);
   // painter->drawLine(end, rightArrowEnd);




} //getDirectedOffset

/**
  Checks whether the point toCheck is in the e-Interval between the two points
 * @brief isSuitedForInterval
 * @param a
 * @param b
 * @return
 */
bool isSuitedForInterval(const QPointF &a, const QPointF &b, const QPointF toCheck){
    qreal epsilon = 10;
    QPointF c = toCheck;

    if(b==a){
        return false;
    }

    qreal dX = b.x()-a.x();
    qreal dY = b.y()-a.y();
    qreal m;

    qreal dXCB = b.x()-c.x();
    qreal dYCB = b.y()-c.y();

    qreal dXCA = a.x()-c.x();
    qreal dYCA = a.y()-c.y();

    qreal dXCBAbs = dXCB<0 ? -dXCB : dXCB;
    qreal dXCAAbs = dXCA<0 ? -dXCA : dXCA;
    qreal dYCBAbs = dYCB<0 ? -dYCB : dYCB;
    qreal dYCAAbs = dYCA<0 ? -dYCA : dYCA;

    qreal dXAbs = dX<0 ? -dX : dX;
    qreal dYAbs = dY<0 ? -dY : dY;

    //first check: see whether the initial point was between these two by checking if it is inside the bounds
    if(dXCBAbs>dXAbs || dXCAAbs>dXAbs || dYCAAbs>dYAbs|| dYCBAbs>dYAbs){
        //out of x or y bounds
        DEBUG(not suited because outside of first check);
        return false;
    }

    if(dX!=0){
        m=dY/dX;
        qreal phi = atan(m);
        qreal correctDYCB = dXCB*tan(phi);
        qreal correctDYCA = dXCA*tan(phi);
        if(dYCB >=(correctDYCB-epsilon) && dYCB<=(correctDYCB+epsilon)){
            //seen from B, it is in interval
            if(dYCA>=(correctDYCA-epsilon) && dYCA<=(correctDYCA+epsilon)){
                //also from A
              //  DEBUG(seuited);
                return true;
            }
        }
       // DEBUG(not suited);
        return false;
    }/*
    else{
        m=dX/dY;
        qreal phi = -atan(m);
        qreal correctDYCB = dXCB*tan(phi);
        qreal correctDYCA = dXCA*tan(phi);
        if(dYCB >=(correctDYCB-epsilon) && dYCB<=(correctDYCB+epsilon)){
             //seen from B, it is in interval
             if(dYCA>=(correctDYCA-epsilon) && dYCA<=(correctDYCA+epsilon)){
                 //also from A
                 DEBUG(suited);
                 return true;
             }
        }
        DEBUG(not suited);
        return false;
    }*/

} //isSuitedForInterval

/**
 * @brief MovementExerciseItem::MovementExerciseItem
 * @param parentGameObject
 * @param mw
 */
MovementExerciseItem::MovementExerciseItem(GraphicsExerciseItem *parentGameObject, Ui_ExerciseMainWindow *mw, QPointF end):
    mw(mw),
    gameObject(parentGameObject),
    scene(mw->getCurrentScene()),
    end(end)
{
    points = new QPointFVector();
    points->emplace_back(end);
    mw->graphicsView->viewport()->update();
}//constructor

/**
 * @brief MovementExerciseItem::~MovementExerciseIendtem
 */
MovementExerciseItem::~MovementExerciseItem(){
    delete(points);
    DEBUG(deleted MovementItem (destructor called));
}// destructor

/**
 * @brief MovementExerciseItem::setEnd
 * @param endPoint
 */
void MovementExerciseItem::setEnd(QPointF endPoint) {
    this->end = endPoint;
    points->clear();

    points->emplace_back(end);

}//setEnd

/**
 * @brief MovementExerciseItem::boundingRect
 * @return
 */
QRectF MovementExerciseItem::boundingRect() const
{
    qreal xMin, xMax, yMin, yMax;

    // do stuff to determine them
    xMin = gameObject->scenePos().x();
    xMax = gameObject->scenePos().x();
    yMin = gameObject->scenePos().y();
    yMax = gameObject->scenePos().y();
    for(auto iter = points->begin(); iter!=points->end(); ++iter){
        qreal y = (*iter).y();
        qreal x = (*iter).x();
        yMin = y<yMin ? y : yMin;
        xMin = x<xMin ? x : xMin;
        yMax = y>yMax ? y : yMax;
        xMax = x>xMax ? x : xMax;
    }

    return QRectF(xMin, yMin, xMax-xMin, yMax-yMin);


}//boundingRect

void MovementExerciseItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    QPen pen (Qt::darkGreen);
    pen.setWidth(4);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    QPointF pOff = gameObject->scenePos();
    pOff+= QPointF(gameObject->tool->getCursor()->pixmap().width()/2, gameObject->tool->getCursor()->pixmap().height()/2);
    QPointF p1 = pOff;
    QPointF p2;
    for (auto iter = points->begin(); iter!=points->end(); ++iter){
        p2 = (*iter);
        painter->setPen(pen);
        painter->drawLine(p1, p2);
        pen.setWidth(10);
        pen.setColor(Qt::darkRed);
        painter->setPen(pen);
        painter->drawPoint(p2);
        pen.setWidth(4);
        pen.setColor(Qt::darkGreen);
        p1 = p2;
    }

    //paintMovementArrowHead(pOff, end, painter);


}//paint

/**
 * @brief MovementExerciseItem::getPoints
 * @return
 */
QPointFVector* MovementExerciseItem::getPoints() const{
    return this->points;
} //getPoints;

/**
 * @brief MovementExerciseItem::getEndPoint
 * @return
 */
QPointF MovementExerciseItem::getEndPoint() const{
    return end;
}//getEnd();

/**
 * @brief MovementExerciseItem::mouseReleaseEvent
 * @param event
 */
void MovementExerciseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    DEBUG(mouseReleaseEvent() on movementitem);
    if(event->button()==Qt::LeftButton){
        isLeftClicked = false;

        if(event->scenePos()!=initialClickPosition){
            //introduce bended path

            QPointF a = gameObject->scenePos();
            QPointF b;
            bool isInserted = false;
            for (auto iter = points->begin(); iter !=points->end(); ++iter){
                b = (*iter);
                if(isInserted){
                    //do nothin
                }
                else if (isSuitedForInterval(a, b, initialClickPosition)){
                    // is between these two grid points a and b
                    QPointF grid = event->scenePos();
                    auto newIter =  points->insert(iter, grid);
                    iter = newIter;
                    iter++;
                    DEBUG(inserted);

                }
                a=b;

            }
        }
        this->mw->graphicsView->viewport()->update();

    }//leftButton
    else if(event->button()==Qt::RightButton){
        isRightClicked = false;
        int n = 20;

        insertEquidistantGridPoints(n);
    }
    else  if(event->button()==Qt::MiddleButton){
        //middle button deletes the element
        DEBUG(mouse mid released on movementItem);
        scene->removeItem(this);
        gameObject->movementItem = Q_NULLPTR;

        this->mw->graphicsView->viewport()->update();
        delete(this);
    }
    else{
         QGraphicsItem::mouseReleaseEvent(event);
    }
    mw->graphicsView->viewport()->update();


}// mouseReleaseEvent


/**
 * @brief MovementExerciseItem::mousePressEvent
 * @param event
 */
void MovementExerciseItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   DEBUG(mousePressEvent() on MovementItem);
    initialClickPosition = event->scenePos();
    if(event->button()==Qt::LeftButton){
        isLeftClicked = true;
       // QGraphicsItem::mousePressEvent(event);
    }
    else if(event->button()==Qt::RightButton){
        isRightClicked = true;
     //   QGraphicsItem::mousePressEvent(event);
    }
    else{
        //QGraphicsItem::mousePressEvent(event);
    }

    this->mw->graphicsView->viewport()->update();
}//mousePressEvent

#ifdef MOUSE_EVENTS_MOVEMENTEXERCISEITEM__
/**
 * @brief MovementExerciseItem::mouseMoveEvent
 * @param event
 */
void MovementExerciseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}//mouseMoveEvent

/**
 * @brief MovementExerciseItem::mouseDoubleClickEvent
 * @param event
 */
void MovementExerciseItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}//mouseDoubleClickEvent

#endif //MOUSE_EVENT_MOVEMENT

/**
 * @brief MovementExerciseItem::getPathLength
 * @return
 */
qreal MovementExerciseItem::getPathLength() const{
    qreal len = 0;
    QPointF a = gameObject->scenePos();
    QPointF b;
    for(auto iter = points->begin(); iter!=points->end(); ++iter){
        b = (*iter);
        qreal dX = b.x()-a.x();
        qreal dY = b.y()-a.y();
        qreal sum = pow(dX, 2)+pow(dY, 2);
        len+=sqrt(sum);

        a=b;
    }
    LDEBUG(len);
    return len;
}//getPathLength

/**
 * @brief MovementExerciseItem::insertEquidistantGridPoints
 * @param numStagesTotal
 */
void MovementExerciseItem::insertEquidistantGridPoints(int numStagesTotal){
    if(numStagesTotal<=0) return;

    LDEBUG(points->size()<< "old size");

    qreal len = getPathLength();
    qreal stageLen = len/numStagesTotal;
    LDEBUG(len << "lenTotal");
    LDEBUG(stageLen << "stageLen");
    int numStages = numStagesTotal;
    QPointF pOff = gameObject->scenePos();
    pOff+= QPointF(gameObject->tool->getCursor()->pixmap().width()/2, gameObject->tool->getCursor()->pixmap().height()/2);

    for(int ii=0; ii<numStagesTotal; ii++){
    QPointF a = pOff;
    QPointF b;
    for(auto iter = points->begin(); iter!=points->end(); ++iter){
        b=(*iter);
        qreal dX = b.x()-a.x();
        qreal dY = b.y()-a.y();
        qreal sum = pow(dX, 2)+pow(dY, 2);
        sum = sqrt(sum);
        if(sum>=1.3*stageLen){
            // we'll have to insert a stage then
            qreal m;
            qreal newX;
            qreal newY;
            if(dX!=0){
                m=dY/dX;
                //if(m<0) m*=-1;
                qreal bX = a.y() > b.y() ? a.y() : b.y();
                qreal bY = a.x() > b.x() ? a.x() : b.x();

                newY = a.y()+sin(atan(m))*stageLen;
                newX = a.x()+cos(atan(m))*stageLen;
                if(b.x()<a.x()){
                    newY = a.y()-sin(atan(m))*stageLen;
                    newX = a.x()-cos(atan(m))*stageLen;
                }

            }else if(dX==0 && dY == 0){
                //same point at start and end;
                newY = a.y();
                newX = a.x();
            }

            else{
                newY = a.y() > b.y() ? a.y() -stageLen : b.y()-stageLen;
                newX = a.x() > b.x() ? a.y() -stageLen : b.y()-stageLen;
            }
            QPointF newP(newX, newY);

            auto newIter = points->insert(iter, newP);
            numStages--;
            iter=newIter;
            //iter++;
        }
        a=b;

    }
    }// for ii
    LDEBUG(points->size()<< "newSize");
    this->mw->graphicsView->viewport()->update();

}//insertEquidistantGridPoints

/**
 * @brief MovementExerciseItem::gameObject
 * @return
 */
GraphicsExerciseItem* MovementExerciseItem::getGameObject() const{
    return this->gameObject;
}//getGameObject
