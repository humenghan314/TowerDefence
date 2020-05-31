#ifndef PEOPLE_H
#define PEOPLE_H
#include "tfobj.h"
#include <QImage>
#include <QPainter>

//待保护的东西，有生命等属性
class People:public TFObj{
public:
    People(){this->setHitPoint(1);}//当有三个敌人接触到people时people死亡
    void underAttack(int x,int y);//传入敌人的坐标
};

#endif // PEOPLE_H
