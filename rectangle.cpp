#include "rectangle.h"

Rectangle::Rectangle()
{

}

void Rectangle::drawing(qreal a, qreal b){
    vector.resize(4);
    vector[0] = {- a / 2, b / 2};
    vector[1] = {a / 2, b / 2};
    vector[2] = {a / 2, - b / 2};
    vector[3] = {- a / 2, - b / 2};

    draw = false;

    repaint();
}
