#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <polygon.h>


class Rectangle : public Polygon
{
public:
    Rectangle();

    void drawing(qreal a, qreal b);

};

#endif // RECTANGLE_H
