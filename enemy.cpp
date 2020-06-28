#include "enemy.h"
#include <iostream>
#include <sstream>
#include <QPoint>


Enemy::Enemy(string type){
    this->setHitPoint(60);
    this->damage=5;
    this->steps=10;
    this->layer=0;
    if(type=="easy"){
        string corner="000 310 190 310 190 110 470 110 470 430 750 430 750 240 810 240 810 180";
        for(int i=0;i<9;i++){
            int x,y;
            string tmp=corner.substr(8*i,7);
            istringstream istrStream(tmp);
            istrStream>>x>>y;
            path.push_back(QPoint(x,y));
        }
    }else{
        string corner="000 450 450 450 450 300 150 300 150 170 450 170 450 060 660 060 660 180 810 180";
        for(int i=0;i<10;i++){
            int x,y;
            string tmp=corner.substr(8*i,7);
            istringstream istrStream(tmp);
            istrStream>>x>>y;
            path.push_back(QPoint(x,y));
        }
    }
}
void Enemy::show(QPainter *painter){
    TFObj::show(painter);
    setDamageX(this->getX()+this->getLen()/2.0);
    setDamageY(this->getY()+this->getWid()/2.0);
    painter->setPen(QPen(Qt::red,3,Qt::SolidLine));
    painter->drawRect(this->getX(),this->getY()-5,40,3);

    painter->setPen(QPen(Qt::green,3,Qt::SolidLine));
    painter->drawRect(this->getX(),this->getY()-5,this->getHitPoint()/60.0*40.0,3);
}
void Enemy::move(QPoint A,QPoint B){//每执行一次函数，只走一步(10单位)
    if(A.x()==B.x()){
        if(A.y()<B.y()){
            this->setY(this->getY()+steps);
        }else{
            this->setY(this->getY()-steps);
        }
    }
    if(A.y()==B.y()){
        if(A.x()<B.x()){
            this->setX(this->getX()+steps);
        }else{
            this->setX(this->getX()-steps);
        }
    }
}
void Enemy::underAttack(int x, int y, int r, int damageValue){
    int tmp=(this->getDamageX()-x)*(this->getDamageX()-x)+(this->getDamageY()-y)*(this->getDamageY()-y);
    if(tmp<=r*r){
        this->setHitPoint(this->getHitPoint()-damageValue);
    }
}
void Enemy::getDebuff(int x, int y, int r, int percent){
    int tmp=(this->getDamageX()-x)*(this->getDamageX()-x)+(this->getDamageY()-y)*(this->getDamageY()-y);
    if(tmp<=r*r){
        this->damage=this->damage*(100-percent)/100;
        this->layer+=1;
    }

}

bool betweenPoints(QPoint A, QPoint B, QPoint C){
    if((C.x()-A.x())*(B.x()-C.x())>=0){
        if((C.y()-A.y())*(B.y()-C.y())>=0){
            return 1;
        }else return 0;
    }else return 0;
}
void Enemy::ManageEnemyMove(){
    //设置几个转弯点
    int n=path.size();
    for(int i=0;i<n-1;i++){
        if(betweenPoints(path[i],path[i+1],QPoint(this->getX(),this->getY()))){
            if(path[i+1]==QPoint(this->getX(),this->getY())&&i<n-2){
                move(path[i+1],path[i+2]);
            }else{
                move(path[i],path[i+1]);
            }
            break;
        }
    }
}
