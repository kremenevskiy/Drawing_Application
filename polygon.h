#ifndef POLYGON_H
#define POLYGON_H

#include <figure.h>


class Polygon : public Figure
{

public:
    Polygon();

    void drawing(int n, qreal R);
};

#endif // POLYGON_H
