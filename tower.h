#ifndef TOWER_H
#define TOWER_H
#include "tfobj.h"

class Tower:public TFObj{
public:
    Tower();
    void showArea(QPainter *painter);

    virtual string towerType(){return "Tower";}
    int getRadius(){return radius;}
    void setRadius(int r){radius=r;}
    virtual int getDamageValue(){return 0;}
    virtual void setDamageValue(int dam){}
    virtual int getDecreaseValue(){return 0;}
    virtual void setDecreaseValue(int dec){}
    virtual ~Tower(){}
private:
    int radius;//aoe攻击半径
};
#endif // TOWER_H
