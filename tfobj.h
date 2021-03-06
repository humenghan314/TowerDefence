#ifndef TFOBJ_H
#define TFOBJ_H
#include <QPainter>
#include <string>
using namespace std;

class TFObj{
public:
    TFObj(){}

    void setX(int x){_x=x;}
    void setY(int y){_y=y;}
    int getX(){return _x;}
    int getY(){return _y;}
    void setDamageX(double x){damage_x=x;}
    void setDamageY(double y){damage_y=y;}
    double getDamageX(){return damage_x;}
    double getDamageY(){return damage_y;}

    void setName(string name){_name=name;}
    void setPicture(QImage pic){_picture=pic;}

    void setLen(int len){_length=len;}
    void setWid(int wid){_width=wid;}
    int getLen(){return _length;}
    int getWid(){return _width;}

    void setHitPoint(int hp){this->hitPoint=hp;}
    int getHitPoint(){return hitPoint;}

    virtual void show(QPainter * painter);//绘制obj
    void initObj(string name,int x,int y);//获得初始坐标+图片+图片大小(依据每个物体的名字来初始化)
    virtual ~TFObj(){}
private:
    int _x,_y;
    int damage_x,damage_y;
    int _length,_width;
    QImage _picture;
    string _name;
    int hitPoint;//生命值(方便起见，设置子弹也具有生命值，当子弹击中目标后生命值清零)
};

#endif // TFOBJ_H
