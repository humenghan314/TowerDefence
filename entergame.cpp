#include "entergame.h"
#include "ui_entergame.h"
#include <QTimer>
#include <QIcon>
#include <iostream>
#include <sstream>

static int birthnum=1;

enterGame::enterGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::enterGame)
{
    ui->setupUi(this);
    tfgame.initWorld();
    setFixedSize(960,640);//设置窗体大小为固定值，后续根据需要再改进

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(PaintEnemyMove()));
    timer->start(500);

    timer0 = new QTimer(this);
    connect(timer0,SIGNAL(timeout()),this,SLOT(PaintEnemyBirth()));
    timer0->start(3000);

    attacktime=new QTimer(this);
    connect(attacktime,SIGNAL(timeout()),this,SLOT(Tower_LaunchAttack()));


    QIcon towerbase(":/picture/towergame/building.png");
    string tower_position="320 280 320 320 370 280";
    /*_towerBase.push_back(new QPushButton(this));
    for(int i=0;i<3;i++){
        int x,y;
        string tmp=tower_position.substr(8*i,7);
        istringstream istrStream(tmp);
        istrStream>>x>>y;
        tower_set[i].setIcon(towerbase);
        tower_set[i].setIconSize(QSize(50,30));
        tower_set[i].setFlat(true);
        tower_set[i].setGeometry(x,y,50,30);
        connect(setTower[i],&QPushButton::clicked,this,[=](){
            this->tfgame.setTower(x,y);
            this->repaint();
            attacktime->start(1000);//在存在炮台的时候才能开始计时开始调用underAttack
        });
    }*/
   /* gameTime = new QTimer(this);
    gameTime->start(30000);*/


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
