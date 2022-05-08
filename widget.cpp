 #include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new Scene(this);
    scene->setSceneRect(0,0,1114, 645);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->addBird(scene->width() / 4, scene->height() / 2);
    //setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}
Widget::~Widget()
{
    delete ui;
}


//void Widget::on_startGameButton_clicked()
//{
//    scene->startGame();
//}

