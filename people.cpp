#include "people.h"

void People::underAttack(int x,int y){
    if(x==this->getX()&&y==this->getY()){
        this->setHitPoint(this->getHitPoint()-1);//设置people的生命值在遇到一次敌人就减1，而非减去敌人攻击的数值
    }
}
