#include "tower.h"
#include <sstream>
#include <string>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <iostream>

Tower::Tower(){

}
void Tower::showArea(QPainter *painter){
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->setPen(QPen(Qt::white,2,Qt::SolidLine));
    painter->drawEllipse(this->getX()-60,this->getY()-30,2*this->radius,2*this->radius);
}
