#include "variedenemy.h"
#include <iostream>

Shielder::Shielder(string type):Enemy(type){
    this->shield_damage=30;
    shield = new QImage(":/picture/towergame/shield.png");
    (*shield)=(*shield).scaled(75,75);
}
void Shielder::show(QPainter * painter){
    Enemy::show(painter);
    //绘制盾牌
    if(shield!=NULL){
        painter->drawImage(this->getX()-15,this->getY(),*shield);
    }
}
Shielder::~Shielder(){
    delete shield;
}
void Shielder::underAttack(int x, int y, int r, int damageValue){
    int tmp=(this->getDamageX()-x)*(this->getDamageX()-x)+(this->getDamageY()-y)*(this->getDamageY()-y);
    if(tmp<=r*r){
        if(this->shield_damage<=0){
            this->setHitPoint(this->getHitPoint()-damageValue);
        }
        else{
            this->shield_damage-=damageValue;
            if(shield_damage<=0){
                delete shield;
                shield=0;
            }
        }
    }
}
