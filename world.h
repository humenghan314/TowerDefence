#ifndef WORLD_H
#define WORLD_H
#include "tfobj.h"
#include "people.h"
#include "enemy.h"
#include "tower.h"
#include <QPainter>
#include <vector>
#include <string>
using namespace std;

class World
{
public:
    World();
    ~World();
    void initEnemy();//初始化敌人
    void initWorld();//世界的初始化，与按键信号有关(依据不同难度系数初始化，不同系数下存放的物体以及坐标不同)
    void showWorld(QPainter *painter);//绘制世界
    void EnemyMove();//敌方的移动
    void peopleErase();
    void enemyErase(Enemy** e);
    bool peopleDeath(){return _peopledeath;}
    void setTower(int x,int y);
    void launchAttack(int x,int y,int r,int damage);
    //void BulletMove(int direction,int step);(第一版炮台为aoe攻击方式，不考虑子弹追随敌人攻击)
private:
    QImage _background;
    vector <Enemy*> _enemy;
    vector <Tower*> _tower;
    People * _people;
    int _peopledeath=0;
};

#endif // WORLD_H
