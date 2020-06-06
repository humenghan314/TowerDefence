#ifndef ENTERGAME_H
#define ENTERGAME_H

#include <QMainWindow>
#include "world.h"
#include <QTimer>
#include <QPainter>
#include <QImage>
#include <QPushButton>
#include <vector>
namespace Ui {
class enterGame;
}

class enterGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit enterGame(QWidget *parent = 0);
    ~enterGame();
    void paintEvent(QPaintEvent *event);
protected slots:
    void PaintEnemyMove();//绘制随时间变化敌人的移动
    void PaintEnemyBirth();
    //void GameOver();//当
    void Tower_LaunchAttack();
private:
    Ui::enterGame *ui;
    World tfgame;
    QTimer* timer;//敌人移动
    QTimer* timer0;//敌人刷新
    QTimer* attacktime;//炮台攻击频率
    //QTimer* gameTime;//游戏计时
};

#endif // ENTERGAME_H
