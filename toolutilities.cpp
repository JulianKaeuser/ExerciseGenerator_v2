#include "toolutilities.h"
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QRegion>



#define SQRT2 1.41
#define RSQRT2 0.705
#define LAG_OFFSET 10

#include <iostream>
#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)

///*
///*
// * enum toolType{
//
//    player = 0,
//    forward = 1,
//    forwardPuck = 2,
//    defender =3,
//    defenderPuck = 4,
//    puck = 5,
//    pucks = 6,
//    pass = 7,
//    slapshot = 8,
//    wristshot = 9,
//    queue = 10,
//    forwardQueue = 11,
//    defenderQueue = 12
//};
//
//
///**
// * @brief getSelectedCursor
// * @param t
// * @param color
// * @return
// */
//QCursor* getSelectedCursor(toolType t, QColor color){
//    QCursor *qC;
//    switch(t){
//    case(puck):{
//        QImage *q = new QImage(":/imageSources/puck.png");
//        QImage qs = q->scaledToHeight(10);
//        qC = new QCursor(QPixmap::fromImage(qs), -1, -1);
//        break;
//    }
//    case(pucks):{
//        QImage *q = new QImage(":/imageSources/pucks.png");
//
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//    case(player):{
//        QImage *q = new QImage(":/imageSources/player.png");
//        q = changeBaseColor(q, color);
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//    case(forward):{
//        QString text ("F");
//        QImage *q = new QImage(":/imageSources/player.png");
//        q = changeBaseColor(q, color);
//        QPainter qp (q);
//        qp.drawText(10, 10, text);
//        qp.end();
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//    case(forwardPuck):{
//        QString text ("F");
//        QImage *q = new QImage(":/imageSources/player.png");
//        q = changeBaseColor(q, color);
//        QPainter qp (q);
//        qp.drawText(10, 10, text);
//        qp.end();
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//    case(defender):{
//        QString text ("D");
//        QImage *q = new QImage(":/imageSources/player.png");
//        q = changeBaseColor(q, color);
//        QPainter qp (q);
//        qp.drawText(10, 10, text);
//        qp.end();
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//    case(defenderPuck):{
//        QString text ("D");
//        QImage *q = new QImage(":/imageSources/player.png");
//        q = changeBaseColor(q, color);
//        QPainter qp (q);
//        qp.drawText(10, 10, text);
//        qp.end();
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//    case(pass):{
//        QImage *q = new QImage(":/imageSources/pass.png");
//        q = changeBaseColor(q, color);
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//    case(slapshot):{
//        QImage *q = new QImage(":/imageSources/slapshot.png");
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//    case(wristshot):{
//        QImage *q = new QImage(":/imageSources/wristshot.png");
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//    case(forwardQueue):{
//        QString text ("F");
//        QImage *q = new QImage(":/imageSources/line.png");
//        q = changeBaseColor(q, color);
//        QPainter qp (q);
//        qp.drawText(10, 10, text);
//        qp.end();
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//    case(defenderQueue):{
//        QString text ("D");
//        QImage *q = new QImage(":/imageSources/line.png");
//        q = changeBaseColor(q, color);
//        QPainter qp (q);
//        qp.drawText(10, 10, text);
//        qp.end();
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//    case(queue):{
//        QImage *q = new QImage(":/imageSources/line.png");
//        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
//        break;
//    }
//
//
//    default:{
//        break;
//    }
//    }
//    return qC;
//}
//
///**
// * @brief getSelectedColor
// * @param combo
// * @return
// */
//QColor* getSelectedColor(QComboBox *combo){
//    QColor *qc;
//    int index = combo->currentIndex();
//
//    switch(index){
//    case(0):{
//        qc = new QColor(Qt::black);
//        break;
//    }
//    case (1):{
//        qc = new QColor(Qt::red);
//        break;
//    }
//    case (2):{
//        qc = new QColor(Qt::white);
//        break;
//    }
//    case (3):{
//        qc = new QColor(Qt::yellow);
//        break;
//    }
//    case (4):{
//        qc = new QColor(Qt::green);
//        break;
//    }
//    case (5):{
//        qc = new QColor(Qt::blue);
//        break;
//    }
//    default:
//        qc = new QColor(Qt::black);
//        break;
//    }
//
//    return qc;
//}
//
///**
// * @brief changeBaseColor
// * @param image
// * @param color
// * @return
// */
//QImage* changeBaseColor(QImage* image, QColor color){
//    for (int ii = 0; ii<image->height(); ii++){
//        for (int jj = 0; jj<image->width(); jj++){
//            QRgb pix = image->pixel(jj, ii);
//            if (pix == QColor(Qt::black).rgb()){
//                image->setPixel(jj, ii, color.rgb());
//            }
//        }
//    }
//    return image;
//}
//
///**
// * @brief turnCursor
// * @param cursor
// * @param degree
// * @param text
// * @return
// */
//QCursor* turnCursor(QCursor cursor, int degree){
//    QPixmap pixmap = cursor.pixmap();
//    int oldH = pixmap.height();
//    pixmap = pixmap.scaledToHeight(oldH);
//
//
//    QTransform transform;
//    QTransform trans = transform.rotate(degree);
//
//
//    QPixmap *transPixmap = new QPixmap(pixmap.transformed(trans));
//    QCursor *nCursor = (new QCursor(*transPixmap));
//
//    return nCursor;
//}
//
//// deprecated
//QPoint* getMappedPoint(QPoint *point, QImage *image, PaintLabel *label){
//    // point = coordinates in label coordinates
//    //QPixmap *pix = label->pixmap();
//    QSize pixSize = label->pixmap()->size();
//    double relativeHeightOfPoint = (double (point->y()))/(double (label->height()));
//    double relativeWidthOfPoint = (double(point->x()))/(double (label->width()));
//    //LDEBUG(relativeHeightOfPoint);
//    //LDEBUG(relativeWidthOfPoint);
//    int imageRelativeX = (image->width())*relativeWidthOfPoint;
//    int imageRelativeY = (image->height())*relativeHeightOfPoint;
//
///*
//    if(imageRelativeX<LAG_OFFSET){
//        imageRelativeX = 0;
//    }
//    else{
//        imageRelativeX -=LAG_OFFSET;
//    }
//    if(imageRelativeY<LAG_OFFSET){
//        imageRelativeY = 0;
//    }
//    else{
//        imageRelativeY -=LAG_OFFSET;
//    }*/
//
//    QPoint *imageRelativePoint = new QPoint(imageRelativeX, imageRelativeY);
//
//    return imageRelativePoint;
//};
//
///**
// * @brief getColorOfArrowByTool
// * @return
// */
//QColor* getColorOfArrowByTool(toolType type) {
//    //DEBUG(getColorOfArrowByTool(toolType) called);
//    QColor t = Qt::blue;
//    switch(type){
//    case(puck):{
//        t = Qt::black;
//        break;
//    }
//    case(player):{
//        t = Qt::darkMagenta;
//        break;
//    }
//    case(forward):{
//        t = Qt::darkMagenta;
//        break;
//    }
//    case(defender):{
//        t = Qt::darkMagenta;
//        break;
//    }
//    case(slapshot):{
//        t = Qt::green;
//        break;
//    }
//    case(wristshot):{
//        t = Qt::green;
//        break;
//    }
//    default:{
//        t = Qt::black;
//        break;
//    }
//    }
//    QColor *p = new QColor(t);
//    return p;
//}
//
//*/
//
