#ifndef WORLD_H
#define WORLD_H
#include "tfobj.h"
#include "people.h"
#include "enemy.h"
#include "variedenemy.h"
#include "variedtower.h"
#include "gameover.h"
#include "tower.h"
#include <QPainter>
#include <vector>
#include <string>
#include <QMediaPlayer>
using namespace std;

class World{
public:
    World();
    ~World();
    void initEnemy(string type);//初始化敌人

    void initWorld(string type);//世界的初始化，与按键信号有关(依据不同难度系数初始化，不同系数下存放的物体以及坐标不同)
    void showWorld(QPainter *painter);//绘制世界

    void EnemyMove();//敌方的移动

    int peopleDeath(){return _peopledeath;}
    int ifWin();

    void setTower(int x,int y,string type);
    void deleteTower(int x,int y);
    void towerLevelUp(int x,int y);

    void launchAttack(int x,int y);

    QString getMoney();
    int getMoneyNum(){return money;}
private:
    QImage _background;
    string gameType;
    int initY;
    int money;
    vector <Enemy*> _enemy;
    vector <Tower*> _tower;
    People * _people;
    int _peopledeath=0;
};

#endif // WORLD_H
