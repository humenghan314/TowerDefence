#include "variedenemy.h"

Shielder::Shielder(){
    this->shield_damage=10;
}
void Shielder::show(QPainter * painter){
    TFObj::show(painter);
    //绘制盾牌
}
void Shielder::underAttack(int x, int y, int r, int damageValue){
    int tmp=(this->getX()-x)*(this->getX()-x)+(this->getY()-y)*(this->getY()-y);
    if(tmp<=r*r){
        if(this->shield_damage==0){
            //绘制盾牌破裂
            this->setHitPoint(this->getHitPoint()-damageValue);
        }
        else{
            this->shield_damage-=damageValue;
        }
    }
}
