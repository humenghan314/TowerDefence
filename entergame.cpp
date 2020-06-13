#include "entergame.h"
#include "ui_entergame.h"
#include <QTimer>
#include <QIcon>
#include <iostream>
#include <sstream>

static int birthnum=1;
static int wavenum=0;

enterGame::enterGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::enterGame)
{
    ui->setupUi(this);
    tfgame=new World;

    tfgame->initWorld();
    setFixedSize(960,640);//设置窗体大小为固定值

    win.load(":/picture/win.png");
    win=win.scaled(960,640);
    lose.load(":/picture/lose.png");
    lose=lose.scaled(960,640);

    showOver=new gameOver();
    connect(showOver,SIGNAL(myReturnSignal()),this,SLOT(sentSignal()));


    moveTime = new QTimer(this);
    connect(moveTime,SIGNAL(timeout()),this,SLOT(PaintEnemyMove()));

    ifLose = new QTimer(this);
    connect(ifLose,SIGNAL(timeout()),this,SLOT(LoseGame()));

    waveTime = new QTimer(this);
    connect(waveTime,SIGNAL(timeout()),this,SLOT(enemyWave()));

    birthTime = new QTimer(this);//同一波内敌人刷新时间间隔
    connect(birthTime,SIGNAL(timeout()),this,SLOT(PaintEnemyBirth()));

    gameTime = new QTimer(this);
    connect(gameTime,SIGNAL(timeout()),this,SLOT(WinGame()));

    QIcon towerbase(":/picture/towergame/building.png");
    string tower_position="280 230 280 320 370 230 550 400 650 400";
    for(int i=0;i<5;i++){
        int x,y;
        QPushButton* choose=new QPushButton(this);//点击后跳转到选择界面
        string tmp=tower_position.substr(8*i,7);
        istringstream istrStream(tmp);
        istrStream>>x>>y;
        choose->setIcon(towerbase);
        choose->setIconSize(QSize(50,30));
        choose->setFlat(true);
        choose->setGeometry(x,y,50,30);

        QGroupBox* thisGroupBox=new QGroupBox(this);//选择界面
        QPushButton* thisNewTower1=new QPushButton("攻击型塔");
        QPushButton* thisNewTower2=new QPushButton("减益型塔");
        QPushButton* thisDeleteTower=new QPushButton("拆塔");
        QPushButton* thisLevelUp=new QPushButton("升级");
        QVBoxLayout *vLayout = new QVBoxLayout();//布局
        thisGroupBox->setGeometry(x+50, y+30, 100, 150);
        thisGroupBox->setVisible(false);
        vLayout->addWidget(thisNewTower1);
        vLayout->addWidget(thisNewTower2);
        vLayout->addWidget(thisDeleteTower);
        vLayout->addWidget(thisLevelUp);
        thisGroupBox->setLayout(vLayout);

        QTimer* thisAttackTime=new QTimer(this);
        connect(thisAttackTime,&QTimer::timeout,this,[=](){
            tfgame->launchAttack(x,y);
        });

        connect(choose,&QPushButton::clicked,this,[=](){
            thisGroupBox->show();
        });
        connect(thisNewTower1,&QPushButton::clicked,this,[=](){
            this->tfgame->setTower(x,y,"ArrowTower");
            this->repaint();
            thisGroupBox->hide();
            thisAttackTime->start(1000);//在存在炮台的时候才能开始计时开始调用underAttack
        });
        connect(thisNewTower2,&QPushButton::clicked,this,[=](){
            this->tfgame->setTower(x,y,"DebuffTower");
            this->repaint();
            thisGroupBox->hide();
            thisAttackTime->start(1000);//在存在炮台的时候才能开始计时开始调用underAttack
        });
        connect(thisDeleteTower,&QPushButton::clicked,this,[=](){
            tfgame->deleteTower(x,y);
            thisGroupBox->hide();
        });
        connect(thisLevelUp,&QPushButton::clicked,this,[=](){
            tfgame->towerLevelUp(x,y);
            this->repaint();
            thisGroupBox->hide();
        });
        _towerBase.push_back(choose);
        _groupBox.push_back(thisGroupBox);
        _newTower1.push_back(thisNewTower1);
        _newTower2.push_back(thisNewTower2);
        _deleteTower.push_back(thisDeleteTower);
        _levelUp.push_back(thisLevelUp);
        _attacktime.push_back(thisAttackTime);
    }
   /* gameTime = new QTimer(this);
    gameTime->start(30000);*/

}

enterGame::~enterGame()
{
    delete ui;
}
void enterGame::paintEvent(QPaintEvent *){
    QPainter *painter = new QPainter();
    painter->begin(this);
    tfgame->showWorld(painter);
    painter->end();
    delete painter;
}
void enterGame::PaintEnemyMove(){
    this->tfgame->EnemyMove();
    this->repaint();
}
void enterGame::enemyWave(){
    wavenum++;
    if(wavenum==1){
        birthTime->start(3000);
        waveTime->start(25000);
    }
    else if(wavenum==2){
        birthTime->start(1500);
    }
    else if(wavenum==3){
        waveTime->stop();
    }
    cout<<"wavenum"<<wavenum<<endl;
}
void enterGame::PaintEnemyBirth(){
    if(wavenum==1||wavenum==3){
        this->tfgame->initEnemy("knight");
        this->repaint();
        if(birthnum==5){
            birthTime->stop();
            birthnum=1;
        }
        birthnum++;
    }
    else if(wavenum==2){
        this->tfgame->initEnemy("shielder");
        this->repaint();
        if(birthnum==5){
            birthTime->stop();
            birthnum=1;
        }
        birthnum++;
    }
    cout<<"birthnum"<<birthnum<<endl;
}
void enterGame::WinGame(){
    this->close();
    showOver->setImage(win);
    showOver->show();
}
void enterGame::LoseGame(){
    if(tfgame->peopleDeath()==1){
        this->close();
        showOver->setImage(lose);
        showOver->show();
    }
}

void enterGame::newTimer(){//初始
    moveTime->start(500);
    ifLose->start(1000);
    waveTime->start(1000);//时间修改10秒一波
    gameTime->start(120000);//一局游戏最长时间
}
void enterGame::sentSignal(){
    emit myReturnSignal2();
}
