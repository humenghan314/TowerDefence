#include "world.h"
#include <iostream>
#include <math.h>
using namespace std;

World::World(){
    this->_people = new People;
    this->money=200;
}
World::~World(){
    delete this->_people;
}

QString World::getMoney(){
    QString str=QString::number(money);
    str=str+"¥";
    return str;
}

//初始化世界、敌人、建塔
void World::initWorld(string type){
    if(type=="easy"){
        this->_background.load(":/picture/towergame/map_two.jpg");
        this->gameType="easy";
        this->initY=310;
    }
    else{
        this->_background.load(":/picture/towergame/map_one.jpg");
        this->gameType="hard";
        this->initY=450;
    }
    this->_people->initObj("people",810,180);
}
void World::initEnemy(string type){//应该要传入一个字符串 根据字符串初始化不同的敌人
    if(type=="shielder"){
        Enemy* p=new Shielder(gameType);
        p->initObj("shielder",0,initY);
        _enemy.push_back(p);
    }
    else if(type=="knight"){
        Enemy* p=new Knight(gameType);
        p->initObj("knight",0,initY);
        _enemy.push_back(p);
    }
}

void World::setTower(int x,int y,string type){
    if(type=="ArrowTower"){
        Tower* p=new ArrowTower;
        p->initObj("ArrowTower",x-15,y-70);
        _tower.push_back(p);
        this->money-=150;
    }
    else if(type=="DebuffTower"){
        Tower* p=new DebuffTower;
        p->initObj("DebuffTower",x-15,y-70);
        _tower.push_back(p);
        this->money-=200;
    }
}
void World::deleteTower(int x,int y){
    vector<Tower*>::iterator it;
    it = _tower.begin();
    while(it!=_tower.end()){
        if((*it)->getX()==(x-15)&&(*it)->getY()==(y-70)){//注意因为qt绘图的坐标始终在右上角所以存在位移，需要对xy进行加减
            delete (*it);
            it = this->_tower.erase(it);
            this->money+=100;
            break;
        }
        else{
            it++;
        }
    }
}
void World::towerLevelUp(int x,int y){
    vector<Tower*>::iterator it;
    it = _tower.begin();
    while(it!=_tower.end()){
        if((*it)->getX()==(x-15)&&(*it)->getY()==(y-70)){
            if((*it)->towerType()=="ArrowTower"){
                (*it)->setDamageValue((*it)->getDamageValue()+10);
            }
            else if((*it)->towerType()=="DebuffTower"){
                (*it)->setDecreaseValue((*it)->getDecreaseValue()+10);
            }
            (*it)->setHitPoint(200);
            (*it)->setRadius((*it)->getRadius()+40);
            this->money-=50;
            break;
        }
        else{
            it++;
        }
    }
}

//塔攻击敌人,以及敌人的死亡
void World::launchAttack(int x,int y){
    int n=this->_tower.size();
    for(int i=0;i<n;i++){
        if(_tower[i]->getX()==(x-15)&&_tower[i]->getY()==(y-70)){//先对塔定位
            if(_tower[i]->towerType()=="DebuffTower"){
                vector<Enemy*>::iterator it;
                it = _enemy.begin();
                while(it!=_enemy.end()){
                    if((*it)->getLayer()<1){
                        (*it)->getDebuff(_tower[i]->getDamageX(),_tower[i]->getDamageY(),_tower[i]->getRadius(),_tower[i]->getDecreaseValue());
                    }
                    it++;
                }
            }
            else if(_tower[i]->towerType()=="ArrowTower"){
                vector<Enemy*>::iterator it;
                it = _enemy.begin();
                while(it!=_enemy.end()){
                    (*it)->underAttack(_tower[i]->getDamageX(),_tower[i]->getDamageY(),_tower[i]->getRadius(),_tower[i]->getDamageValue());
                    if ((*it)->getHitPoint()<=0){
                        delete (*it);
                        it = this->_enemy.erase(it);
                        this->money+=50;
                     }
                    else{
                        it++;
                    }
                }
            }
            break;
        }
    }
}
int World::ifWin(){
    int n=_enemy.size();
    if(n==0){
        return 1;
    }
    else return 0;
}

//绘制
void World::showWorld(QPainter *painter){
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->drawImage(0,0,_background);//坐标系是以左上角为零点
    int n = this->_enemy.size();
    for (int i=0;i<n;i++){
        this->_enemy[i]->show(painter);
    }

    this->_people->show(painter);

    int m = this->_tower.size();
    for (int i=0;i<m;i++){
        this->_tower[i]->show(painter);
        this->_tower[i]->showArea(painter);
    }
}

//敌人的移动（同时处理是否有敌人到达终点攻击公主）
void World::EnemyMove(){//设置敌人移动的路径，设立几个转弯点传入方向使用TFObj类的move
    int n = this->_enemy.size();
    for (int i=0;i<n;i++){
        if(_enemy[i]->enemyType()=="Shielder"){
            this->_enemy[i]->ManageEnemyMove();
        }
        else if(_enemy[i]->enemyType()=="Knight"){
            int isTower=0;
            vector <Tower*>::iterator ittower;
            for(ittower=_tower.begin();ittower!=_tower.end();ittower++){
                int tmp=(_enemy[i]->getDamageX()-(*ittower)->getDamageX())*(_enemy[i]->getDamageX()-(*ittower)->getDamageX())+(_enemy[i]->getDamageY()-(*ittower)->getDamageY())*(_enemy[i]->getDamageY()-(*ittower)->getDamageY());
                if(tmp<=12100){
                    isTower=1;
                    (*ittower)->setHitPoint((*ittower)->getHitPoint()-_enemy[i]->getDamageValue());
                    if((*ittower)->getHitPoint()<=0){
                        delete (*ittower);
                        ittower = this->_tower.erase(ittower);
                        break;
                    }
                }
            }
            if(isTower==0){
                this->_enemy[i]->ManageEnemyMove();
            }
        }
        this->_people->underAttack(this->_enemy[i]->getX(),this->_enemy[i]->getY());
        if(this->_people->getHitPoint()<=0){
            _peopledeath=1;
        }
    }
}

