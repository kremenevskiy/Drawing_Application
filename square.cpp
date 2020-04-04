#include "square.h"

Square::Square()
{

}


void Square::drawing(qreal a){
    vector.resize(4);
    vector[0] = {-a / 2, a / 2};
    vector[1] = {a / 2, a / 2};
    vector[2] = {a / 2, - a / 2};
    vector[3] = {- a / 2, - a / 2};

    draw = false;

    repaint();
}
