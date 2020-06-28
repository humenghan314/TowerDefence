#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(960,640);
    game_one=new enterGame("easy");
    game_two=new enterGame("hard");

    QIcon ico(":/picture/version_easy.png");
    ui->version_easy->setIcon(ico);
    ui->version_easy->setIconSize(QSize(200,100));
    ui->version_easy->setFlat(true);
    ui->version_easy->setGeometry(380,400,200,100);

    QIcon ico2(":/picture/version_hard.png");
    ui->version_hard->setIcon(ico2);
    ui->version_hard->setIconSize(QSize(200,100));
    ui->version_hard->setFlat(true);
    ui->version_hard->setGeometry(380,500,200,100);

    connect(ui->version_easy,SIGNAL(clicked()),this,SLOT(on_version_easy_clicked()));
    connect(ui->version_hard,SIGNAL(clicked()),this,SLOT(on_version_hard_clicked()));

    connect(game_one,enterGame::myReturnSignal2,this,[=](){
            this->show();
            music->play();
            delete game_one;
            game_one=NULL;
        });
    connect(game_two,enterGame::myReturnSignal2,this,[=](){
            this->show();
            music->play();
            delete game_two;
            game_two=NULL;
        });

    music=new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/sound/towergame/LoadingBgm.mp3"));
    music->setVolume(30);
    music->play();
}
void MainWindow::paintEvent(QPaintEvent *){
    QPainter *painter;
    painter = new QPainter();
    painter->begin(this);
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->drawImage(0,0,QImage(":/picture/homePage.jpg"));
    painter->end();
    delete painter;
}
MainWindow::~MainWindow()
{
    delete ui;
    delete game_one;
    delete game_two;
}
void MainWindow::on_version_easy_clicked()
{
    this->hide();
    music->stop();
    if(game_one!=NULL){
        game_one->show();
        game_one->newTimer();
    }else{
        game_one=new enterGame("easy");
        game_one->show();
        game_one->newTimer();
    }
}
void MainWindow::on_version_hard_clicked()
{
    this->hide();
    music->stop();
    if(game_two!=NULL){
        game_two->show();
        game_two->newTimer();
    }else{
        game_two=new enterGame("hard");
        game_two->show();
        game_two->newTimer();
    }
}
