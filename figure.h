#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#define PIXEL_SM 50

#include <vector>
#include <cmath>
#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>


class Figure : public QGraphicsScene
{
public:
    explicit Figure(QObject *parent = nullptr);
    //~Figure();

    std::vector<QPointF> vector;

    bool draw = true;
    bool drawPoint = true;
    bool showSup = false;

    QPointF previousPoint, startPoint;
    QPointF pointSup, pointCnt;
    QPointF helpPoint;


public:
    void drawing();

    void move(qreal dx, qreal dy);
    void zoom (qreal a);
    void rotate(qreal a);
    QPointF rotatePoint(QPointF base, QPointF point, qreal a);

    void deleteSup();

    qreal LEN(QPointF a, QPointF b);
    qreal SQR(QPointF A, QPointF B, QPointF C);
    QPointF CENTER_M();

    virtual qreal perimeter();
    virtual qreal square();


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    virtual void repaint();

};

#endif // FIGURE_H
