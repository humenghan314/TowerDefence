#include "enemy.h"
#include <iostream>
Enemy::Enemy(){
    this->setHitPoint(10);
    this->damage=10;
}
void Enemy::move(int direction){//每执行一次函数，只走一步(10单位)
    //direction1234(上下左右wsad)
    switch (direction){
        case 1:
            this->setY(this->getY()-50);
            break;
        case 2:
            this->setY(this->getY()+50);
            break;
        case 3:
            this->setX(this->getX()-50);
            break;
        case 4:
            this->setX(this->getX()+50);
            break;
    }
}
void Enemy::underAttack(int x, int y,int damageValue){
    if(x==this->getX()&&y==this->getY()){//修正，敌人不是点
        this->setHitPoint(this->getHitPoint()-damageValue);
    }
}
void Enemy::underAttack(int x, int y, int r, int damageValue){
    int tmp=(this->getX()-x)*(this->getX()-x)+(this->getY()-y)*(this->getY()-y);
    cout<<tmp<<endl;
    if(tmp<=r*r){
        cout<<"underAttack"<<endl;
        this->setHitPoint(this->getHitPoint()-damageValue);
    }
}
