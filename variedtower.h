#ifndef VARIEDTOWER_H
#define VARIEDTOWER_H
#include "tower.h"

class ArrowTower:public Tower{
public:
    ArrowTower();
    string towerType(){return "ArrowTower";}
    int getDamageValue(){return damageValue;}
    void setDamageValue(int dam){damageValue=dam;}
private:
    int damageValue;
};


class DebuffTower : public Tower{
public:
    DebuffTower();
    string towerType(){return "DebuffTower";}
    int getDecreaseValue(){return decreaseValue;}
    void setDecreaseValue(int dec){decreaseValue=dec;}
private:
    int decreaseValue;//减益幅度
};

#endif // VARIEDTOWER_H
