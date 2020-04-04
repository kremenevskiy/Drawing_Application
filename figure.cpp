#include "figure.h"


Figure::Figure(QObject *parent) : QGraphicsScene(parent)
{

}


void Figure::move(qreal dx, qreal dy){

    for(unsigned long i = 0; i < vector.size(); i++){
        vector[i] = {vector[i].x() + dx, vector[i].y() + dy};
    }

    pointCnt = {pointCnt.x() + dx, pointCnt.y() + dy};

    repaint();
}


void Figure::zoom(qreal a){

    for (unsigned long i = 0; i < vector.size(); i++) {
        vector[i] = {pointSup.x() + (vector[i].x() - pointSup.x()) * a,
                     pointSup.y() + (vector[i].y() - pointSup.y()) * a};
    }

    pointCnt = {pointSup.x() + (pointCnt.x() - pointSup.x()) * a,
                pointSup.y() + (pointCnt.y() - pointSup.y()) * a};
    repaint();
}


void Figure::rotate(qreal a){

    for(unsigned long i = 0; i < vector.size(); i++) {
        vector[i] = rotatePoint(pointSup, vector[i], a);
    }

    pointCnt = rotatePoint(pointSup, pointCnt, a);
    repaint();

}


QPointF Figure::rotatePoint(QPointF base, QPointF point, qreal a){

    qreal dx, dy, newDx, newDy;
    dx = point.x() - base.x();
    dy = point.y() - base.y();

    newDx = dx * cos(a) - dy * sin(a);
    newDy = dx * sin(a) + dy * cos(a);

    return {base.x() + newDx, base.y() + newDy};
}



void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event){

    QPointF point = event->scenePos();

    if (draw){

        addEllipse(point.x() - 5, point.y() - 5, 10, 10);
        vector.push_back(point);
        startPoint = point;
        drawPoint = false;
    }

    previousPoint = point;
    helpPoint = point;
}


void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    if (draw){
        QPointF point = event->scenePos();
        vector.push_back(point);
        addLine(previousPoint.x(), previousPoint.y(), point.x(), point.y());
    }
    else{
        qreal dx = event->scenePos().x() - previousPoint.x();
        qreal dy = event->scenePos().y() - previousPoint.y();
        move(dx, dy);
    }

    previousPoint = event->scenePos();
}


void Figure::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    if (draw){
        addLine(previousPoint.x(), previousPoint.y(), startPoint.x(), startPoint.y());
        draw = false;
        pointCnt = CENTER_M();
    }

    else if (helpPoint == previousPoint) { // Перемещаю вспомогательную точку, если сама фигура не двигалась
        pointSup = event->scenePos();
        showSup = true;

    }
    repaint();

}


void Figure::repaint(){

    clear();
    for(unsigned long i = 0; i < vector.size(); i++){
        addLine(vector[i].x(), vector[i].y(), vector[(i+1) % vector.size()].x(), vector[(i+1) % vector.size()].y());
    }

    addEllipse(pointCnt.x() - 3, pointCnt.y() - 3, 7, 7, QPen(Qt::black), QBrush(Qt::red));
    if (showSup) addEllipse(pointSup.x() - 5, pointSup.y() - 5, 10, 10, QPen(Qt::green), QBrush(Qt::gray));
}


void Figure::drawing(){
    repaint();
}


qreal Figure::LEN(QPointF a, QPointF b){

    return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}


qreal Figure::SQR(QPointF A, QPointF B, QPointF C){

    qreal a, b, c, p;
    a = LEN(A, B);
    b = LEN(B, C);
    c = LEN(C, A);
    p = (a + b + c) / 2;

    return sqrt(p * (p - a) * (p - b) * (p - c));
}


QPointF Figure::CENTER_M(){

    double S = 0, x = 0,y = 0;

    for(unsigned long i = 0; i < vector.size(); i++){

        double s = SQR(vector[0], vector[i], vector[(i+1) % vector.size()]);
        S += s;
        x += s * (vector[0].x() + vector[i].x() + vector[(i+1) % vector.size()].x()) / 3;
        y += s * (vector[0].y() + vector[i].y() + vector[(i+1) % vector.size()].y()) / 3;
    }

    if (S == 0) return vector[0];
    x /= S;
    y /= S;

    return {x, y};
}


qreal Figure::square(){

    qreal S = 0;
    for(unsigned long i = 0; i < vector.size(); i++) {
        qreal s = SQR(vector[0], vector[i], vector[(i+1) % vector.size()]);
        S += s;
    }
    return S / PIXEL_SM / PIXEL_SM;
}


void Figure::deleteSup()
{

    showSup = false;
    pointSup = pointCnt;
    repaint();
}


qreal Figure::perimeter(){

    qreal P = 0;
    for(unsigned long i = 0; i < vector.size(); i++) {
        qreal p = LEN(vector[i], vector[(i+1) % vector.size()]);
        P += p;
    }
    return P / PIXEL_SM;
}
