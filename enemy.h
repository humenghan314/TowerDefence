#ifndef ENEMY_H
#define ENEMY_H
#include "tfobj.h"
#include <string>
#include <QPoint>
class Enemy:public TFObj{
public:
    Enemy(string type);
    void show(QPainter *painter);
    void move(QPoint A,QPoint B);

    virtual void underAttack(int x, int y,int r,int damageValue);//传入炮台的攻击范围（炮台坐标和攻击半径）、攻击强度
    void getDebuff(int x,int y,int r,int percent);
    void setLayer(int x){this->layer=x;}
    int getLayer(){return layer;}

    void ManageEnemyMove();

    int getDamageValue(){return damage;}
    virtual string enemyType(){return "enemy";}
private:
    int damage;//敌人一次伤害的数值
    int steps;//每次移动的距离
    int layer;//获得debuff的层数（防止debuff叠加或者导致step数据变为负数）
    vector<QPoint>path;
};

bool betweenPoints(QPoint A,QPoint B,QPoint C);
#endif // ENEMY_H
