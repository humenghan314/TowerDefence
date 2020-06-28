#include "entergame.h"
#include "ui_entergame.h"
#include <QTimer>
#include <QIcon>
#include <iostream>
#include <sstream>

static int birthnum=1;
static int wavenum=0;

enterGame::enterGame(string s,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::enterGame)
{
    ui->setupUi(this);
    tfgame=new World;
    if(s=="easy"){
        tfgame->initWorld("easy");
        _type="easy";
    }else{
        tfgame->initWorld("hard");
        _type="hard";
    }
    setFixedSize(960,640);//设置窗体大小为固定值

    win.load(":/picture/win.png");
    win=win.scaled(960,640);
    lose.load(":/picture/lose.png");
    lose=lose.scaled(960,640);
    endBgm=new QMediaPlayer(this);
    gameBgm=new QMediaPlayer(this);
    gameBgm->setMedia(QUrl("qrc:/sound/towergame/BattleBgm.mp3"));
    gameBgm->setVolume(30);

    showOver=new gameOver();
    connect(showOver,SIGNAL(myReturnSignal()),this,SLOT(sentSignal()));

    moveTime = new QTimer(this);
    connect(moveTime,SIGNAL(timeout()),this,SLOT(PaintEnemyMove()));

    ifLose = new QTimer(this);
    connect(ifLose,SIGNAL(timeout()),this,SLOT(LoseGame()));
    ifWin = new QTimer(this);
    connect(ifWin,&QTimer::timeout,this,[=](){
        if(tfgame->ifWin()==1){
            this->WinGame();
        }
    });

    waveTime = new QTimer(this);
    connect(waveTime,SIGNAL(timeout()),this,SLOT(enemyWave()));

    birthTime = new QTimer(this);//同一波内敌人刷新时间间隔
    connect(birthTime,SIGNAL(timeout()),this,SLOT(PaintEnemyBirth()));

    gameTime = new QTimer(this);
    connect(gameTime,SIGNAL(timeout()),this,SLOT(WinGame()));

    QPixmap moneyImage(":/picture/towergame/money.png");
    ui->ShowMoney->setPixmap(moneyImage);
    ui->ShowMoney->setGeometry(20,15,84,84);
    ui->ShowText->setGeometry(110,30,200,50);
    ui->ShowText->setFont(QFont("Comic Sans MS",30));
    ui->ShowText->setText(tfgame->getMoney());

    warning=new QMessageBox(this);
    warning->move(800,400);
    warning->setWindowTitle("警告");
    warning->setIcon(QMessageBox::Warning);
    warning->setFont(QFont("Microsoft YaHei",10));
    warning->setText("余额不足！");

    QIcon towerbase(":/picture/towergame/building.png");
    string tower_position;
    int towerNum;
    if(_type=="easy"){
        tower_position="280 230 280 320 370 230 550 400 650 400";
        towerNum=5;
    }else{
        tower_position="250 550 350 550 250 410 350 410 250 270 370 150 470 270 550 170";
        towerNum=8;
    }
    for(int i=0;i<towerNum;i++){
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
        QPushButton* thisNewTower1=new QPushButton("攻击型塔(150¥)");
        QPushButton* thisNewTower2=new QPushButton("减益型塔(200¥)");
        QPushButton* thisDeleteTower=new QPushButton("拆塔(100¥)");
        QPushButton* thisLevelUp=new QPushButton("升级(50¥)");
        QPushButton* thisreturn=new QPushButton("取消");
        QVBoxLayout *vLayout = new QVBoxLayout();//布局
        if(y+230>640){
            thisGroupBox->setGeometry(x+50, 440, 150, 200);
        }else{
            thisGroupBox->setGeometry(x+50, y+30, 150, 200);
        }
        thisGroupBox->setVisible(false);
        vLayout->addWidget(thisNewTower1);
        vLayout->addWidget(thisNewTower2);
        vLayout->addWidget(thisDeleteTower);
        vLayout->addWidget(thisLevelUp);
        vLayout->addWidget(thisreturn);
        thisGroupBox->setLayout(vLayout);

        QTimer* thisAttackTime=new QTimer(this);
        connect(thisAttackTime,&QTimer::timeout,this,[=](){
            tfgame->launchAttack(x,y);
            ui->ShowText->setText(tfgame->getMoney());
        });

        connect(choose,&QPushButton::clicked,this,[=](){
            thisGroupBox->show();
        });
        connect(thisNewTower1,&QPushButton::clicked,this,[=](){
            if(tfgame->getMoneyNum()>=150){
                this->tfgame->setTower(x,y,"ArrowTower");
                this->repaint();
                thisAttackTime->start(2000);//在存在炮台的时候才能开始计时开始调用underAttack
                ui->ShowText->setText(tfgame->getMoney());
            }else{
                warning->show();
            }
            thisGroupBox->hide();
        });
        connect(thisNewTower2,&QPushButton::clicked,this,[=](){
            if(tfgame->getMoneyNum()>=200){
                this->tfgame->setTower(x,y,"DebuffTower");
                this->repaint();
                thisAttackTime->start(1000);//在存在炮台的时候才能开始计时开始调用underAttack
                ui->ShowText->setText(tfgame->getMoney());
            }else{
                warning->show();
            }
            thisGroupBox->hide();
        });
        connect(thisDeleteTower,&QPushButton::clicked,this,[=](){
            tfgame->deleteTower(x,y);
            ui->ShowText->setText(tfgame->getMoney());
            thisGroupBox->hide();
        });
        connect(thisLevelUp,&QPushButton::clicked,this,[=](){
            if(tfgame->getMoneyNum()>=50){
                tfgame->towerLevelUp(x,y);
                this->repaint();
                ui->ShowText->setText(tfgame->getMoney());
            }else{
                warning->show();
            }
            thisGroupBox->hide();
        });
        connect(thisreturn,&QPushButton::clicked,this,[=](){
            thisGroupBox->hide();
        });
        _towerBase.push_back(choose);
        _groupBox.push_back(thisGroupBox);
        _newTower1.push_back(thisNewTower1);
        _newTower2.push_back(thisNewTower2);
        _deleteTower.push_back(thisDeleteTower);
        _levelUp.push_back(thisLevelUp);
        _return.push_back(thisreturn);
        _attacktime.push_back(thisAttackTime);
    }
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
    else if(wavenum==2||wavenum==3){
        birthTime->start(1500);
    }
    else if(wavenum==4){
        waveTime->stop();
        birthTime->start(1500);
    }
}
void enterGame::PaintEnemyBirth(){
    if(wavenum==2||wavenum==3){
        this->tfgame->initEnemy("knight");
        this->repaint();
        if(birthnum==5){
            birthTime->stop();
            birthnum=0;
        }
        birthnum++;
    }
    else if(wavenum==1||wavenum==4){
        this->tfgame->initEnemy("shielder");
        this->repaint();
        if(birthnum==8){
            birthTime->stop();
            if(wavenum==4){
                ifWin->start(1000);
            }
            birthnum=0;
        }
        birthnum++;
    }
}
void enterGame::WinGame(){
    gameBgm->stop();
    this->close();
    ifWin->stop();
    endBgm->setMedia(QUrl("qrc:/sound/towergame/WinMusic.mp3"));
    endBgm->setVolume(30);
    endBgm->play();
    showOver->setImage(win);
    showOver->show();
}
void enterGame::LoseGame(){
    if(tfgame->peopleDeath()==1){
        gameBgm->stop();
        this->close();
        ifLose->stop();
        endBgm->setMedia(QUrl("qrc:/sound/towergame/LoseMusic.mp3"));
        endBgm->setVolume(30);
        endBgm->play();
        showOver->setImage(lose);
        showOver->show();
    }
}

void enterGame::newTimer(){//初始
    gameTime->start(180000);//一局游戏最长时间
    waveTime->start(1000);//时间修改10秒一波
    ifLose->start(1000);
    moveTime->start(500);
    gameBgm->play();
}
void enterGame::sentSignal(){
    emit myReturnSignal2();
}
