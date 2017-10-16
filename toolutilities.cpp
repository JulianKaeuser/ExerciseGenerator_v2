#include "toolutilities.h"
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QRegion>
#include "paintlabel.h"


#define SQRT2 1.41
#define RSQRT2 0.705
#define LAG_OFFSET 10

#include <iostream>
#define _LIT(x) # x
#define DEBUG(x) (std::cout << _LIT(x) << std::endl)
#define LDEBUG(x) (std::cout << x << std::endl)
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
 * @brief getSelectedCursor
 * @param t
 * @param color
 * @return
 */
QCursor* getSelectedCursor(toolType t, QColor color){
    QCursor *qC;
    switch(t){
    case(puck):{
        QImage *q = new QImage(":/imageSources/puck.png");
        QImage qs = q->scaledToHeight(10);
        qC = new QCursor(QPixmap::fromImage(qs), qs.height()-8, qs.width()-8);
        break;
    }
    case(pucks):{
        QImage *q = new QImage(":/imageSources/pucks.png");

        qC = new QCursor(QPixmap::fromImage(*q), q->height()-10, q->width()-10);
        break;
    }
    case(player):{
        QImage *q = new QImage(":/imageSources/player.png");
        q = changeBaseColor(q, color);
        qC = new QCursor(QPixmap::fromImage(*q), q->height()-35, q->width()-35);
        break;
    }
    case(forward):{
        QString text ("F");
        QImage *q = new QImage(":/imageSources/player.png");
        q = changeBaseColor(q, color);
        QPainter qp (q);
        qp.drawText(10, 10, text);
        qp.end();
        qC = new QCursor(QPixmap::fromImage(*q), q->height()-35, q->width()-35);
        break;
    }
    case(defender):{
        QString text ("D");
        QImage *q = new QImage(":/imageSources/player.png");
        q = changeBaseColor(q, color);
        QPainter qp (q);
        qp.drawText(10, 10, text);
        qp.end();
        qC = new QCursor(QPixmap::fromImage(*q), q->height()-35, q->width()-35);
        break;
    }
    case(group):{
        QImage *q = new QImage(":/imageSources/group.png");
        q = changeBaseColor(q, color);
        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
        break;
    }
    case(defender_group):{
        QImage *q = new QImage(":/imageSources/defender_group.png");
        q = changeBaseColor(q, color);
        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
        break;
    }
    case(forward_group):{
        QImage *q = new QImage(":/imageSources/forward_group.png");
        q = changeBaseColor(q, color);
        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
        break;
    }
    case(line):{
        QImage *qs = new QImage(":/imageSources/line.png");
        QImage q =  qs->scaledToHeight(qs->height()*0.8);
        q = *changeBaseColor(&q, color);
        QPainter qp (&q);
        qp.end();

        qC = new QCursor(QPixmap::fromImage(q), -1, -1);
        break;
    }
    case(forward_line):{
        QString text ("F");
        QImage *qs = new QImage(":/imageSources/line.png");
        QImage q =  qs->scaledToHeight(qs->height()*0.8);
        q = *changeBaseColor(&q, color);
        QPainter qp (&q);
        qp.drawText(10, 11, text);
        qp.end();

        qC = new QCursor(QPixmap::fromImage(q), -1, -1);
        break;
    }
    case(defender_line):{
        QString text ("D");
        QImage *qs = new QImage(":/imageSources/line.png");
        QImage q =  qs->scaledToHeight(qs->height()*0.8);
        q = *changeBaseColor(&q, color);
        QPainter qp (&q);
        qp.drawText(10, 11, text);
        qp.end();

        qC = new QCursor(QPixmap::fromImage(q), -1, -1);
        break;
    }
        //non-elemnt types
    case(turn):{
        QImage *q = new QImage(":/imageSources/turn.png");

        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
        break;
    }
    case(pass):{
        QImage *q = new QImage(":/imageSources/pass.png");
        q = changeBaseColor(q, color);
        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
        break;
    }

    case(stickhandling):{
        QImage *q = new QImage(":/imageSources/stickhandling.png");

        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
        break;
    }
    case(slapshot):{
        QImage *q = new QImage(":/imageSources/slapshot.png");
        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
        break;
    }
    case(wristshot):{
        QImage *q = new QImage(":/imageSources/wristshot.png");
        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
        break;
    }
    case(runway):{
        QImage *q = new QImage(":/imageSources/runway.png");

        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
        break;
    }
    case(runway_with_puck):{
        QImage *q = new QImage(":/imageSources/runway_with_puck.png");

        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
        break;
    }
    case(backwards):{
        QImage *q = new QImage(":/imageSources/backwards.png");

        qC = new QCursor(QPixmap::fromImage(*q), -1, -1);
        break;
    }

    default:{
        break;
    }
    }
    return qC;
}

/**
 * @brief getSelectedColor
 * @param combo
 * @return
 */
QColor* getSelectedColor(QComboBox *combo){
    QColor *qc;
    int index = combo->currentIndex();

    switch(index){
    case(0):{
        qc = new QColor(Qt::black);
        break;
    }
    case (1):{
        qc = new QColor(Qt::red);
        break;
    }
    case (2):{
        qc = new QColor(Qt::white);
        break;
    }
    case (3):{
        qc = new QColor(Qt::yellow);
        break;
    }
    case (4):{
        qc = new QColor(Qt::green);
        break;
    }
    case (5):{
        qc = new QColor(Qt::blue);
        break;
    }
    default:
        qc = new QColor(Qt::black);
        break;
    }

    return qc;
}

/**
 * @brief changeBaseColor
 * @param image
 * @param color
 * @return
 */
QImage* changeBaseColor(QImage* image, QColor color){
    for (int ii = 0; ii<image->height(); ii++){
        for (int jj = 0; jj<image->width(); jj++){
            QRgb pix = image->pixel(jj, ii);
            if (pix == QColor(Qt::black).rgb()){
                image->setPixel(jj, ii, color.rgb());
            }
        }
    }
    return image;
}

/**
 * @brief turnCursor
 * @param cursor
 * @param degree
 * @param text
 * @return
 */
QCursor* turnCursor(QCursor cursor, int degree, QString *text){
    QPixmap pixmap = cursor.pixmap();
    int oldH = pixmap.height();
    pixmap = pixmap.scaledToHeight(oldH);


    QTransform transform;
    QTransform trans = transform.rotate(degree);


    QPixmap *transPixmap = new QPixmap(pixmap.transformed(trans));
    QCursor *nCursor = (new QCursor(*transPixmap));

    return nCursor;
}

QPoint* getMappedPoint(QPoint *point, QImage *image, PaintLabel *label){
    // point = coordinates in label coordinates
    //QPixmap *pix = label->pixmap();
    QSize pixSize = label->pixmap()->size();
    double relativeHeightOfPoint = (double (point->y()))/(double (label->height()));
    double relativeWidthOfPoint = (double(point->x()))/(double (label->width()));
    //LDEBUG(relativeHeightOfPoint);
    //LDEBUG(relativeWidthOfPoint);
    int imageRelativeX = (image->width())*relativeWidthOfPoint;
    int imageRelativeY = (image->height())*relativeHeightOfPoint;

/*
    if(imageRelativeX<LAG_OFFSET){
        imageRelativeX = 0;
    }
    else{
        imageRelativeX -=LAG_OFFSET;
    }
    if(imageRelativeY<LAG_OFFSET){
        imageRelativeY = 0;
    }
    else{
        imageRelativeY -=LAG_OFFSET;
    }*/

    QPoint *imageRelativePoint = new QPoint(imageRelativeX, imageRelativeY);

    return imageRelativePoint;
};

/**
 * @brief getColorOfArrowByTool
 * @return
 */
QColor* getColorOfArrowByTool(toolType type) {
    //DEBUG(getColorOfArrowByTool(toolType) called);
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
    case(defender):{
        t = Qt::darkMagenta;
        break;
    }
    case(stickhandling):{
        t = Qt::darkBlue;
        break;
    }
    case(slapshot):{
        t = Qt::green;
        break;
    }
    case(wristshot):{
        t = Qt::green;
        break;
    }
    default:{
        t = Qt::black;
        break;
    }
    }
    QColor *p = new QColor(t);
    return p;
}

ToolUtilities::ToolUtilities()
{

}
