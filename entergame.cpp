#include "entergame.h"
#include "ui_entergame.h"
#include <QTimer>
#include <QIcon>
#include <iostream>

static int birthnum=1;

enterGame::enterGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::enterGame)
{
    ui->setupUi(this);
    tfgame.initWorld();
    setFixedSize(1000,260);//设置窗体大小为固定值，后续根据需要再改进

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(PaintEnemyMove()));
    timer->start(500);

    timer0 = new QTimer(this);
    connect(timer0,SIGNAL(timeout()),this,SLOT(PaintEnemyBirth()));
    timer0->start(3000);

    attacktime=new QTimer(this);
    connect(attacktime,SIGNAL(timeout()),this,SLOT(Tower_LaunchAttack()));


    QIcon ico(":/picture/towerbase.png");
    ui->setTower0->setIcon(ico);
    ui->setTower0->setIconSize(QSize(50,30));
    ui->setTower0->setFlat(true);
    ui->setTower0->setGeometry(500,130,50,30);
   /* gameTime = new QTimer(this);
    gameTime->start(30000);*/

    connect(ui->setTower0,SIGNAL(clicked()),this,SLOT(on_setTower0_clicked()));
}

enterGame::~enterGame()
{
    delete ui;
}
void enterGame::paintEvent(QPaintEvent *){
    QPainter *painter;
    painter = new QPainter();
    painter->begin(this);
    tfgame.showWorld(painter);
    painter->end();
    delete painter;
}
void enterGame::PaintEnemyMove(){
    this->tfgame.EnemyMove();
    this->repaint();
}
void enterGame::PaintEnemyBirth(){
    this->tfgame.initEnemy();
    this->repaint();
    if(birthnum==3){
        timer0->stop();
    }
    birthnum++;
}
/*void enterGame::GameOver(){
    if(gameTime->remainingTime()==0||tfgame.peopleDeath()==1){
        tfgame.~World();
    }
}*/

void enterGame::Tower_LaunchAttack(){
    this->tfgame.launchAttack(500,100,100,10);
    this->repaint();
}
void enterGame::on_setTower0_clicked()
{
    this->tfgame.setTower(500,100);
    this->repaint();
    attacktime->start(1000);//在存在炮台的时候才能开始计时开始调用underAttack
}
