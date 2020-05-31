#include "world.h"
#include <iostream>
using namespace std;

World::World(){
        this->_people = new People;
}
World::~World(){
    if(_peopledeath==0){
        delete this->_people;
    }
}
void World::initWorld(){
    this->_background.load(":/picture/background.png");
    this->_background=this->_background.scaled(1000,260,Qt::KeepAspectRatio);//缩放背景图片大小，后续据需要更改
    this->_people->initObj("people0");

    Enemy* p=new Enemy;
    p->initObj("enemy");
    _enemy.push_back(p);
}
void World::initEnemy(){
    Enemy* p=new Enemy;
    p->initObj("enemy");
    _enemy.push_back(p);
}
void World::setTower(int x, int y){
    Tower* p=new Tower;
    p->initObj(x,y,"tower");
    _tower.push_back(p);
}
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
static int i=1;
void World::launchAttack(int x,int y,int r,int damage){
    vector<Enemy*>::iterator it;
    it = _enemy.begin();
    while(it!=_enemy.end()){
        (*it)->underAttack(x,y,r,damage);
        cout<<(*it)->getHitPoint()<<endl;
        if ((*it)->getHitPoint()==0){
            cout<<"yes"<<endl;
            delete (*it);
            cout<<"yes0"<<endl;
            it = this->_enemy.erase(it);
            break;
         }
        else{
            it++;
        }
    }
    cout<<i<<endl;
    i++;
}
void World::EnemyMove(){//设置敌人移动的路径，设立几个转弯点传入方向使用TFObj类的move(第一版本敌人仅直线)
    int n = this->_enemy.size();
    for (int i=0;i<n;i++){
        //此处有if判断是否是拐弯点再依据拐弯点调整下面move的方向
        this->_enemy[i]->move(4);
        this->_people->underAttack(this->_enemy[i]->getX(),this->_enemy[i]->getY());
        this->peopleErase();
    }
}
/*void World::BulletMove(int direction,int step){

}
*/
void World::peopleErase(){//第一版本不处理炮台，暂且考虑仅产生敌人
    if(this->_people->getHitPoint()==0){
        delete _people;
        this->_peopledeath=1;
        this->_people->setHitPoint(-1);
    }
}

