#ifndef ENEMY_H
#define ENEMY_H
#include "tfobj.h"
#include <string>
class Enemy:public TFObj{
public:
    Enemy();
    void move(int direction);

    virtual void underAttack(int x, int y,int r,int damageValue);//传入炮台的攻击范围（炮台坐标和攻击半径）、攻击强度
    void getDebuff(int x,int y,int r,int percent);

    void ManageEnemyMove();

    int getDamageValue(){return damage;}
    virtual string enemyType(){return "enemy";}
private:
    int damage;//敌人一次伤害的数值
    int steps;//每次移动的距离
};

#endif // ENEMY_H
