#ifndef CIRCLE_H
#define CIRCLE_H

#include <figure.h>


class Circle : public Figure
{

public:
    Circle(QColor setColor);

    QColor color_Circle;

    void drawing(qreal r);
    void repaint();

    qreal perimeter();
    qreal square();
};


#endif // CIRCLE_H
