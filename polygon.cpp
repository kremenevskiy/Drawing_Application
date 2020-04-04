#include "polygon.h"

Polygon::Polygon()
{

}

void Polygon::drawing(int n, qreal R){

    for(int i = 0; i < n; i++){
        vector.push_back({R * cos(2 * M_PI * i / n), R * sin (2 * M_PI * i / n)});
    }

    draw = false;

    repaint();
}
