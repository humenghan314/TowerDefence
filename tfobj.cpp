#include "tfobj.h"
#include <sstream>
using namespace std;
string allInformation="shielder 40 64 people 80 80";//此字符串里包含所有tfobj的名字、出生地点、需要的长宽，此次仅用一个敌人测试

void TFObj::show(QPainter * painter){
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->drawImage(this->_x,this->_y,this->_picture);
}
void TFObj::initObj(string name,int x,int y){
    _x=x;_y=y;_name=name;
    int n=allInformation.find(name);//找到需要初始化的物体的信息
    string tmp=allInformation.substr(n);
    istringstream istrStream(tmp);
    istrStream>>_name>>_length>>_width;

    string path=":/picture/towergame"+name+".png";
    this->_picture.load(path.c_str());
    this->_picture=this->_picture.scaled(this->_length,this->_width,Qt::KeepAspectRatio);

}
