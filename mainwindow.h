#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define PIXEL_SM 50


#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsView>
#include <QRectF>
#include <QRegExpValidator>
#include <cmath>

#include <figure.h>
#include <polygon.h>
#include <rectangle.h>
#include <square.h>
#include <circle.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QString track_Coord;
    QLabel *tr_X;

    QTimer *prmtr_sqrTimer;

    Figure *figure;
    Polygon *polygon;
    Rectangle *rectangle;
    Square *square;
    Circle *circle;

    qreal rotateTO;
    qreal zoomTO;

    enum objects { drawing_custom, drawing_polygon, drawing_rectangle,
                   drawing_square, drawing_circle };

    objects drawing = drawing_custom;


public:
    bool eventFilter(QObject *watched, QEvent *event);


private slots:
    void on_comboBox_currentIndexChanged(int index);
    void update_prmtr_sqr();
    void zoomTime();
    void rotateTime();

    void on_button_plus_clicked();
    void on_button_minus_clicked();
    void on_button_left_clicked();
    void on_button_right_clicked();
    void on_buttonDelete_clicked();
    void on_buttonReDraw_clicked();
};


#endif // MAINWINDOW_H
