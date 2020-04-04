#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(1200, 700);


    tr_X = new QLabel(this);
    ui->statusbar->addWidget(tr_X);

    setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
    //ui->graphicsView->setMouseTracking(true);

    figure = new Figure();
    ui->graphicsView->setScene(figure);
    figure->setSceneRect(0, 0, 1, 1);

    QRegExp exp("[1-9]{2,2}[.]{1,1}[0-9]{1,1}|[1-9]{1,1}[0-9]{0,2}|[1-9]{1,1}[.]{1,1}[0-9]{1,2}");
    QRegExp expINT4("[1-9]{1,1}[0-9]{1,3}");
    QRegExp expINT3("[1-9]{1,1}[0-9]{1,2}");


    QValidator *validator = new QRegExpValidator(exp, this);
    QValidator *validatorINT4 = new QRegExpValidator(expINT4, this);
    QValidator *validatorINT3 = new QRegExpValidator(expINT3, this);


    ui->lineEdit_polygon_N->setValidator(validatorINT4);
    ui->lineEdit_polygon_R->setValidator(validator);
    ui->lineEdit_rectangle_a->setValidator(validator);
    ui->lineEdit_rectangle_b->setValidator(validator);
    ui->lineEdit_square_a->setValidator(validator);
    ui->lineEdit_circle_R->setValidator(validator);
    ui->lineEdit_percents->setValidator(validatorINT3);
    ui->lineEdit_angle->setValidator(validatorINT3);


    prmtr_sqrTimer = new QTimer;

    connect(prmtr_sqrTimer, SIGNAL(timeout()), this, SLOT(update_prmtr_sqr()));
    prmtr_sqrTimer->start(100);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::update_prmtr_sqr(){

    switch (drawing) {

    case drawing_custom:
        if (!figure->draw){
            ui->label_perimeter->setText(QString::number(figure->perimeter()) + " см");
            ui->label_square->setText(QString::number(figure->square()) + " см²");
        }
        break;

    case drawing_polygon:
        ui->label_perimeter->setText(QString::number(polygon->perimeter()) + " см");
        ui->label_square->setText(QString::number(polygon->square()) + " см²");
        break;

    case drawing_rectangle:
        ui->label_perimeter->setText(QString::number(rectangle->perimeter()) + " см");
        ui->label_square->setText(QString::number(rectangle->square()) + " см²");
        break;

    case drawing_square:
        ui->label_perimeter->setText(QString::number(square->perimeter()) + " см");
        ui->label_square->setText(QString::number(square->square()) + " см²");
        break;

    case drawing_circle:
        ui->label_perimeter->setText(QString::number(circle->perimeter()) + " см");
        ui->label_square->setText(QString::number(circle->square()) + " см²");
        break;
    }

    prmtr_sqrTimer->start(100);


}

void MainWindow::zoomTime()
{
    switch (drawing) {

    case drawing_custom:
        figure->zoom(zoomTO);
        break;

    case drawing_polygon:
        polygon->zoom(zoomTO);
        break;

    case drawing_rectangle:
        rectangle->zoom(zoomTO);
        break;

    case drawing_square:
        square->zoom(zoomTO);
        break;

    case drawing_circle:
        circle->zoom(zoomTO);
        break;

    }
}


void MainWindow::rotateTime()
{
    switch (drawing) {

    case drawing_custom:
        figure->rotate(rotateTO);
        break;

    case drawing_polygon:
        polygon->rotate(rotateTO);
        break;

    case drawing_rectangle:
        rectangle->rotate(rotateTO);
        break;

    case drawing_square:
        square->rotate(rotateTO);
        break;

    case drawing_circle:
        circle->rotate(rotateTO);
        break;

    }
}


bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseMove){
        QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);
        QString text;
        text = QString("X: %1 Y: %2").arg(MouseEvent->x()).arg(MouseEvent->y());
        tr_X->setText(text);
    }
}


void MainWindow::on_button_plus_clicked()
{
    double a = ui->lineEdit_percents->text().toDouble();
    a = (a + 100) / 100;
    zoomTO = pow(a, 1.0 / 100);

    for(int i = 0; i < 100; i++){

        QTimer::singleShot(i, this, SLOT(zoomTime()));
    }
}


void MainWindow::on_button_minus_clicked()
{
    double a = ui->lineEdit_percents->text().toDouble();
    a = 100 / (100 + a);
    zoomTO = pow(a, 1.0 / 100);

    for(int i = 0; i < 100; i++){

        QTimer::singleShot(i, this, SLOT(zoomTime()));
    }

}


void MainWindow::on_button_left_clicked()
{
    double a = ui->lineEdit_angle->text().toDouble();
    a = a * M_PI / 180;
    rotateTO = a / 100;

    for (int i = 0; i < 100; i++){
        QTimer::singleShot(i * 3, this, SLOT(rotateTime()));
    }
}


void MainWindow::on_button_right_clicked()
{
    double a = ui->lineEdit_angle->text().toDouble();
    a = - a * M_PI / 180;
    rotateTO = a / 100;

    for (int i = 0; i < 100; i++){
        QTimer::singleShot(i, this, SLOT(rotateTime()));
    }
}


void MainWindow::on_buttonDelete_clicked()
{
    switch (drawing) {

    case drawing_custom:
        figure->deleteSup();
        break;

    case drawing_polygon:
        polygon->deleteSup();
        break;

    case drawing_rectangle:
        rectangle->deleteSup();
        break;

    case drawing_square:
        square->deleteSup();
        break;

    case drawing_circle:
        circle->deleteSup();
        break;
    }
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    int textBox = ui->comboBox->currentIndex();

    switch(textBox){

    case 0:
        drawing = drawing_custom;
        figure = new Figure();
        ui->graphicsView->setScene(figure);
        figure->setSceneRect(0, 0, 1, 1);
        figure->drawing();
        break;

    case 1:
        drawing = drawing_polygon;
        polygon = new Polygon();
        ui->graphicsView->setScene(polygon);
        polygon->setSceneRect(0, 0, 1, 1);
        polygon->drawing(ui->lineEdit_polygon_N->text().toInt(),
                         ui->lineEdit_polygon_R->text().toDouble() * PIXEL_SM);
        break;

    case 2:
        drawing = drawing_rectangle;
        rectangle = new Rectangle();
        ui->graphicsView->setScene(rectangle);
        rectangle->setSceneRect(0, 0, 1, 1);
        rectangle->drawing(ui->lineEdit_rectangle_a->text().toDouble() * PIXEL_SM,
                           ui->lineEdit_rectangle_b->text().toDouble() * PIXEL_SM);
        break;


    case 3:
        drawing = drawing_square;
        square = new Square();
        ui->graphicsView->setScene(square);
        square->setSceneRect(0, 0, 1, 1);
        square->drawing(ui->lineEdit_square_a->text().toDouble() * PIXEL_SM);

        break;

    case 4:
        QColor color = QColor(ui->lineEdit->text().toInt(), ui->lineEdit_2->text().toInt(), ui->lineEdit_3->text().toInt());
        drawing = drawing_circle;
        circle = new Circle(color);
        ui->graphicsView->setScene(circle);
        circle->setSceneRect(0, 0 , 1, 1);
        circle->drawing(ui->lineEdit_circle_R->text().toDouble() * PIXEL_SM);
        break;
    }
}


void MainWindow::on_buttonReDraw_clicked()
{
    int textBox = ui->comboBox->currentIndex();

    switch(textBox){

    case 0:
        drawing = drawing_custom;
        figure = new Figure();
        ui->graphicsView->setScene(figure);
        figure->setSceneRect(0, 0, 1, 1);
        figure->drawing();
        break;

    case 1:
        drawing = drawing_polygon;
        polygon = new Polygon();
        ui->graphicsView->setScene(polygon);
        polygon->setSceneRect(0, 0, 1, 1);
        polygon->drawing(ui->lineEdit_polygon_N->text().toInt(),
                         ui->lineEdit_polygon_R->text().toDouble() * PIXEL_SM);
        break;

    case 2:
        drawing = drawing_rectangle;
        rectangle = new Rectangle();
        ui->graphicsView->setScene(rectangle);
        rectangle->setSceneRect(0, 0, 1, 1);
        rectangle->drawing(ui->lineEdit_rectangle_a->text().toDouble() * PIXEL_SM,
                           ui->lineEdit_rectangle_b->text().toDouble() * PIXEL_SM);
        break;


    case 3:
        drawing = drawing_square;
        square = new Square();
        ui->graphicsView->setScene(square);
        square->setSceneRect(0, 0, 1, 1);
        square->drawing(ui->lineEdit_square_a->text().toDouble() * PIXEL_SM);

        break;

    case 4:
        QColor color = QColor(ui->lineEdit->text().toInt(), ui->lineEdit_2->text().toInt(), ui->lineEdit_3->text().toInt());
        drawing = drawing_circle;
        circle = new Circle(color);
        ui->graphicsView->setScene(circle);
        circle->setSceneRect(0, 0 , 1, 1);
        circle->drawing(ui->lineEdit_circle_R->text().toDouble() * PIXEL_SM);
        break;
    }
}
