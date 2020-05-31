#include "tower.h"
#include <sstream>
#include <string>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <iostream>
string allTower="tower 100 100";//名字、长、宽

Tower::Tower()
{

}
void Tower::initObj(int x,int y,string name){//位置固定为几个点，由button位置决定，传入
    int n=allTower.find(name);//找到需要初始化的物体的信息
    string na=name;
    int wid,len;
    string tmp=allTower.substr(n);
    istringstream istrStream(tmp);
    istrStream>>na>>len>>wid;
    setX(x);setY(y);
    setName(name);
    setLen(len);setWid(wid);

    string path=":/picture/"+name+".png";
    QImage pic;
    pic.load(path.c_str());
    pic=pic.scaled(len,wid,Qt::KeepAspectRatio);
    setPicture(pic);

    radius=100;
    damageValue=10;
    //Area_x=this->getX();
   // Area_y=this->getY()+len/2;
}

void Tower::showArea(QPainter *painter){
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->setPen(QPen(Qt::black,4,Qt::SolidLine));
    painter->drawEllipse(this->getX(),this->getY(),2*this->radius,2*this->radius);
}
