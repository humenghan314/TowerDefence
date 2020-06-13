#include "enemy.h"
#include <iostream>
#include <QPoint>

Enemy::Enemy(){
    this->setHitPoint(10);
    this->damage=10;
    this->steps=10;
}
void Enemy::move(int direction){//每执行一次函数，只走一步(10单位)
    //direction1234(上下左右wsad)
    switch (direction){
        case 1:
            this->setY(this->getY()-steps);
            break;
        case 2:
            this->setY(this->getY()+steps);
            break;
        case 3:
            this->setX(this->getX()-steps);
            break;
        case 4:
            this->setX(this->getX()+steps);
            break;
    }
}
void Enemy::underAttack(int x, int y, int r, int damageValue){
    int tmp=(this->getX()-x)*(this->getX()-x)+(this->getY()-y)*(this->getY()-y);
    if(tmp<=r*r){
        this->setHitPoint(this->getHitPoint()-damageValue);
    }
}
void Enemy::getDebuff(int x, int y, int r, int percent){
    int tmp=(this->getX()-x)*(this->getX()-x)+(this->getY()-y)*(this->getY()-y);
    if(tmp<=r*r){
        this->steps=this->steps*(100-percent)/100;
    }
}

void Enemy::ManageEnemyMove(){
    //设置几个转弯点
    QPoint A(190,310),B(190,110),C(470,110),D(470,430),E(750,430),F(750,240),G(810,200);
    if(this->getX()==190){
        if(this->getY()!=110){
            move(1);
        }
        else{
            move(4);
        }
    }
    else if(this->getX()==470){
        if(this->getY()!=430){
            move(2);
        }
        else{
            move(4);
        }
    }
    else if(this->getX()==750){
        if(this->getY()!=240){
            move(1);
        }
        else{
            move(4);
        }
    }
    else if(this->getX()==810){
        move(1);
    }
    else{
        move(4);
    }
}
