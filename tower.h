#ifndef TOWER_H
#define TOWER_H
#include "tfobj.h"

class Tower:public TFObj{
public:
    Tower();
    void initObj(int x,int y,string name);
    void showArea(QPainter *painter);
private:
    int radius;//aoe攻击半径
    int damageValue;//单次伤害
   // int Area_x;
   // int Area_y;
};
//塔0：范围内间断攻击 r=100 damage=10 x=button_x y=button_y-30
//塔1：范围内持续攻击
//塔3：减速
//塔4：对单个目标挂dot
#endif // TOWER_H
