#include "tower.h"
#include <sstream>
#include <string>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <iostream>
string allTower="ArrowTower 100 100";//名字、长、宽

Tower::Tower()
{

}
void Tower::showArea(QPainter *painter){
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->setPen(QPen(Qt::black,4,Qt::SolidLine));
    painter->drawEllipse(this->getX(),this->getY(),2*this->radius,2*this->radius);
}
