#include "gameover.h"
#include "ui_gameover.h"
#include <iostream>
using namespace std;

gameOver::gameOver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameOver)
{
    ui->setupUi(this);
    setFixedSize(960,640);

    GameReturn=new QPushButton(this);
    QIcon ico2(":/picture/returnGame.png");
    GameReturn->setIcon(ico2);
    GameReturn->setIconSize(QSize(200,100));
    GameReturn->setFlat(true);
    GameReturn->setGeometry(680,500,200,100);
    connect(GameReturn,SIGNAL(clicked()),this,SLOT(click_GameReturn()));
}

gameOver::~gameOver()
{
    delete ui;
}
void gameOver::paintEvent(QPaintEvent *){
    QPainter *painter;
    painter = new QPainter();
    painter->begin(this);
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->drawImage(0,0,showGameOver);
    painter->end();
    delete painter;
}
void gameOver::click_GameReturn(){
    this->hide();
    emit myReturnSignal();
}
