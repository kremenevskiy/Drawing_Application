#ifndef SQUARE_H
#define SQUARE_H

#include <rectangle.h>


class Square: public Rectangle
{
public:
    Square();

    void drawing(qreal a);
};

#endif // SQUARE_H
