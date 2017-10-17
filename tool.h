#ifndef TOOL_H
#define TOOL_H

#include "toolutilities.h"
#include <QColor>
#include <QComboBox>

QColor getColorFromBox(QComboBox*);

enum toolType{

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
};

enum dragType{
    single = 0,
    arrow = -1,
    path = 1
};

class Tool
{
public:
    Tool(toolType, QColor, int);
    Tool (const Tool&);
    ~Tool();
    toolType getToolType();
    QImage* getBaseImage();
    QColor getColor();
    QCursor* getCursor();
    int getCurrentRotation();
    void setRotation(int);
    void setColor(QColor);
    void setType(toolType);
    void rotate(int);
    dragType getDragType();
    QColor getPathColor();

private:
    toolType type;
    QImage *baseImage;
    QColor color;
    QColor pathColor;
    QCursor *cursor;
    int currentRotation;
    dragType dragStatus;
    QImage *puckImage;
};

#endif // TOOL_H
