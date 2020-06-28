#ifndef VARIEDENEMY_H
#define VARIEDENEMY_H
#include "enemy.h"

class Shielder :public Enemy{
public:
    Shielder(string type);
    void show(QPainter * painter);
    void underAttack(int x, int y,int r,int damageValue);
    string enemyType(){return "Shielder";}
    ~Shielder();
private:
    QImage* shield;
    int shield_damage;//盾牌可以承受的伤害总数值
};
class Knight:public Enemy{
public:
    Knight(string type):Enemy(type){}
    string enemyType(){return "Knight";}
    ~Knight(){}
};
#endif // VARIEDENEMY_H
