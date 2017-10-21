#include "tool.h"
#include <QPainter>

#define FORMAT QImage::Format_ARGB32

#include <iostream>
#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

/**
 * @brief getColorFromBox
 * @param box
 * @return
 */
QColor getColorFromBox(QComboBox* box){
    QColor qc = Qt::black;

        int index = box->currentIndex();

        switch(index){
        case(0):{
            break;
        }
        case (1):{
            qc = Qt::red;
            break;
        }
        case (2):{
            qc = Qt::white;
            break;
        }
        case (3):{
            qc = Qt::yellow;
            break;
        }
        case (4):{
            qc = Qt::green;
            break;
        }
        case (5):{
            qc = Qt::blue;
            break;
        }
        default:
            qc = Qt::black;
            break;
        }

        return qc;
}

/**
 * @brief assignColor
 * @param image
 * @param color
 */
void assignColor(QImage *image, QColor color){
    for (int ii = 0; ii<image->height(); ii++){
        for (int jj = 0; jj<image->width(); jj++){
            QRgb pix = image->pixel(jj, ii);
            if (pix == QColor(Qt::black).rgb()){
                image->setPixel(jj, ii, color.rgb());
            }
        }
    }
}//assignColor


/**
 * @brief Tool::Tool
 * @param type
 * @param color
 * @param rotation
 */
Tool::Tool(toolType type, QColor color, int rotation):
    color(color),
    currentRotation(rotation % 360)
{
    puckImage = new QImage(10, 10, FORMAT);
    QPainter painter (puckImage);
    QPen pen (Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(5, 5), 3, 3);
    painter.end();
    this->setType(type);
}// usual constructor

/**
 * @brief Tool::Tool
 * @param other
 */
Tool::Tool(const Tool &other){
    this->color = other.color;
    this->currentRotation = other.currentRotation;
    this->setType(other.type);
} // copy constructor

/**
 * @brief Tool::~Tool
 */
Tool::~Tool(){

    delete(baseImage);
    delete(cursor);
    delete(puckImage);
}//destructor

/**
 * @brief Tool::setType
 * @param type
 */
void Tool::setType(toolType type){

    this->type = type;
    //delete(baseImage);
    //delete(cursor);
/*enum toolType{

    player = 0,
    forward = 1,
    forwardPuck = 2,
    defender =3,
    defenderPuck = 4,
    puck = 5,
    pucks = 6,
    pass = 7,
    slapshot = 8,
    wristshot = 9,
    queue = 10,
    forwardQueue = 11,
    defenderQueue = 12
};*/
    switch(type){
    case(player):{
        baseImage = new QImage(":/imageSources/player.png");
        assignColor(baseImage, this->color);

        this->dragStatus = dragType::path;
        break;
    }
    case(forward):{
        baseImage = new QImage(":/imageSources/player.png");
        assignColor(baseImage, this->color);
        QPainter painter (baseImage);
            QString text("F");
            painter.drawText(10, 10, text);
            painter.end();

        this->dragStatus = dragType::path;
        break;
    }
    case(forwardPuck):{
        baseImage = new QImage(":/imageSources/player.png");
        assignColor(baseImage, this->color);

        QPainter painter (baseImage);
            painter.drawImage(baseImage->height()-12, baseImage->width()-10, *puckImage);
            QString text("D");
            painter.drawText(10, 10, text);
            painter.end();
        this->dragStatus = dragType::path;
        break;
    }
    case(defender):{
        baseImage = new QImage(":/imageSources/player.png");
        assignColor(baseImage, this->color);
        QPainter painter (baseImage);
            QString text("D");
            painter.drawText(10, 10, text);
            painter.end();
        this->dragStatus = dragType::path;
        break;
    }
    case(defenderPuck):{
        baseImage = new QImage(":/imageSources/player.png");
        assignColor(baseImage, this->color);

        QPainter painter (baseImage);
            painter.drawImage(baseImage->height()-12, baseImage->width()-10, *puckImage);
            QString text("D");
            painter.drawText(10, 10, text);
            painter.end();
        this->dragStatus = dragType::path;
        break;
    }
    case(puck):{
         baseImage = new QImage(10, 10, FORMAT);
            QPainter painter (baseImage);
            painter.drawImage(0, 0, *puckImage);
            painter.end();
        this->color = Qt::black;
        this->dragStatus = dragType::path;
        break;
    }
    case(pucks):{
        baseImage = new QImage(":imageSources/pucks.png");

        this->color = Qt::black;
        this->dragStatus = dragType::single;
        break;
    }
    case(pass):{
        baseImage = new QImage(10, 10, FORMAT);
           QPainter painter (baseImage);
           painter.drawImage(0, 0, *puckImage);
           painter.end();
       this->color = Qt::black;
       this->dragStatus = dragType::path;
       break;
    }
    case(slapshot):{
        baseImage = new QImage(10, 10, FORMAT);
           QPainter painter (baseImage);
           painter.drawImage(0, 0, *puckImage);
           painter.end();
       this->color = Qt::black;
       this->dragStatus = dragType::path;
       break;
    }
    case(wristshot):{
        baseImage = new QImage(10, 10, FORMAT);
           QPainter painter (baseImage);
           painter.drawImage(0, 0, *puckImage);
           painter.end();
       this->color = Qt::black;
       this->dragStatus = dragType::path;
       break;
    }
    case(queue):{
        baseImage = new QImage(":/imageSources/line.png");
        assignColor(baseImage, this->color);
        this->dragStatus = dragType::single;
        break;
        break;
    }
    case(forwardQueue):{
        baseImage = new QImage(":/imageSources/line.png");
        assignColor(baseImage, this->color);
        QPainter painter (baseImage);
            QString text("F");
            painter.drawText(10, 10, text);
            painter.end();
        this->dragStatus = dragType::single;
        break;
    }
    case(defenderQueue):{
        baseImage = new QImage(":/imageSources/line.png");
        assignColor(baseImage, this->color);
        QPainter painter (baseImage);
            QString text("D");
            painter.drawText(10, 10, text);
            painter.end();
        this->dragStatus = dragType::single;
        break;
    }
    }
        QTransform transform;
        QTransform trans = transform.rotate(currentRotation);
        QPixmap pix = QPixmap::fromImage(*baseImage);
        QPixmap *pixM = new QPixmap(pix.transformed(trans));
    this->cursor = new QCursor(*pixM, 0, 0);



} // setType

/**
 * @brief Tool::setColor
 * @param color
 */
void Tool::setColor(QColor color){
    this->color = color;
    toolType t = this->type;
    this->setType(t);
} // setColor

/**
 * @brief Tool::setRotation
 * @param rotation
 */
void Tool::setRotation(int rotation){
    this->currentRotation = rotation;
    this->setType(this->type);
} // setRotation

/**
 * @brief Tool::getColor
 * @return
 */
QColor Tool::getColor(){
    return this->color;
} // getColor

/**
 * @brief Tool::getCurrentRotation
 * @return
 */
int Tool::getCurrentRotation(){
    return currentRotation;
} //getCurrentRotation

/**
 * @brief Tool::getCursor
 * @return
 */
QCursor* Tool::getCursor(){
    return this->cursor;
} // getCursor

/**
 * @brief Tool::getBaseImage
 * @return
 */
QImage* Tool::getBaseImage(){
    return this->baseImage;
} // getBaseImage

/**
 * @brief rotate
 * @param degree
 */
void Tool::rotate(int degree){
    this->setRotation(getCurrentRotation()+degree);
}//rotate

/**
 * @brief Tool::getDragType
 * @return
 */
dragType Tool::getDragType(){
    return this->dragStatus;
}//getDragType

/**
 * @brief Tool::getPathColor
 * @return
 */
QColor Tool::getPathColor(){

    if(getDragType()==single){
        return Qt::black;
    }
    if(getDragType()==arrow){
        return Qt::green;
    }

    QColor t = Qt::blue;
    switch(type){
    case(puck):{
        t = Qt::black;
        break;
    }
    case(player):{
        t = Qt::darkMagenta;
        break;
    }
    case(forward):{
        t = Qt::darkMagenta;
        break;
    }
    case(forwardPuck):{
        t = Qt::darkMagenta;
        break;
    }
    case(defender):{
        t = Qt::darkRed;
        break;
    }
    case(defenderPuck):{
        t = Qt::darkRed;
        break;
    }
    case(pass):{
        t = Qt::darkCyan;
        break;
    }
    default:{
        t = Qt::darkBlue;
        break;
    }
    }
    return t;
}//getPathColor

