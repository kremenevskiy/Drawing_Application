#include "circle.h"

Circle::Circle(QColor setColor)
{
    color_Circle = setColor;
}

void Circle::drawing(qreal r){

    vector.resize(4);
    vector[0] = {r, 0};
    vector[1] = {0, -r};
    vector[2] = {-r, 0};
    vector[3] = {0, r};

    draw = false;
    repaint();
}


void Circle::repaint(){

    qreal radious = LEN(vector[0], vector[2]) / 2;
    clear();

    addEllipse(pointCnt.x() - radious, pointCnt.y() - radious, radious * 2, radious * 2, QPen(Qt::red), QBrush(color_Circle));
    addEllipse(pointCnt.x() - 3, pointCnt.y() - 3, 7, 7, QPen(Qt::black), QBrush(Qt::red));
    if (showSup) addEllipse(pointSup.x(), pointSup.y(), 10, 10, QPen(Qt::green), QBrush(Qt::gray));

}


qreal Circle::perimeter(){

    qreal radious = LEN(vector[0], vector[2]) / 2;
    return 2 * M_PI * radious / PIXEL_SM;
}


qreal Circle::square(){

    qreal radious = LEN(vector[0], vector[2]) / 2;
    return M_PI * radious * radious / PIXEL_SM / PIXEL_SM;
}
