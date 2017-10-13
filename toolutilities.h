#ifndef TOOLUTILITIES_H
#define TOOLUTILITIES_H

#include <QCursor>
#include <QColor>
#include <QComboBox>
#include <QPoint>

// forward declaration
class PaintLabel;

enum toolType{
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

QCursor* getSelectedCursor(toolType, QColor);

QColor* getSelectedColor(QComboBox* );

QImage* changeBaseColor(QImage* , QColor);

QCursor* turnCursor(QCursor, int, QString*);

QPoint* getMappedPoint(QPoint*, QImage*, PaintLabel*);

QColor* getColorOfArrowByTool(toolType);

class ToolUtilities
{
public:
    ToolUtilities();
};

#endif // TOOLUTILITIES_H
