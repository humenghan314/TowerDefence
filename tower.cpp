#include "tower.h"
#include <sstream>
#include <string>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <iostream>

Tower::Tower(){
    this->radius=100;
    this->setHitPoint(200);
}
void Tower::showArea(QPainter *painter){
    painter->setPen(QPen(Qt::red,3,Qt::SolidLine));
    painter->drawRect(this->getX()+10,this->getY()+5,60,3);
    painter->setPen(QPen(Qt::green,3,Qt::SolidLine));
    painter->drawRect(this->getX()+10,this->getY()+5,this->getHitPoint()/200.0*60.0,3);

    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->setPen(QPen(Qt::white,2,Qt::SolidLine));
    setDamageX(this->getX()+this->getLen()/2.0);
    setDamageY(this->getY()+this->getWid()/2.0);
    painter->drawEllipse(getDamageX()-this->radius,getDamageY()-this->radius,2*this->radius,2*this->radius);
}
