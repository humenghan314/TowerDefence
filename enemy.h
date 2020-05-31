#ifndef ENEMY_H
#define ENEMY_H
#include "tfobj.h"

class Enemy:public TFObj{
public:
    Enemy();
    void move(int direction);
    void underAttack(int x,int y,int damageValue);//传入炮台发射的子弹的坐标、攻击强度
    void underAttack(int x, int y,int r,int damageValue);//传入炮台的攻击范围（炮台坐标和攻击半径）、攻击强度
private:
    int damage;//敌人一次伤害的数值
};

#endif // ENEMY_H
