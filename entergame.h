#ifndef ENTERGAME_H
#define ENTERGAME_H

#include <QMainWindow>
#include "world.h"
#include "gameover.h"
#include <QTimer>
#include <QPainter>
#include <QImage>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMultimedia>
#include <vector>
namespace Ui {
class enterGame;
}

class enterGame : public QMainWindow
{
    Q_OBJECT

public:
    //explicit enterGame(QWidget *parent = 0);
    explicit enterGame(string s,QWidget *parent = 0);
    ~enterGame();
    void paintEvent(QPaintEvent *event);
    void newTimer();
signals:
    void myReturnSignal2();
protected slots:
    void PaintEnemyMove();//绘制随时间变化敌人的移动
    void PaintEnemyBirth();
    void enemyWave();
    void WinGame();
    void LoseGame();
    void sentSignal();
private:
    Ui::enterGame *ui;

    World* tfgame;
    string _type;

    QMessageBox* warning;
    QTimer* moveTime;//敌人移动
    QTimer* birthTime;//敌人刷新
    QTimer* waveTime;
    QTimer* gameTime;//控制整个游戏进程
    QTimer* ifLose;
    QTimer* ifWin;

    QImage win;
    QImage lose;
    QMediaPlayer* endBgm;
    QMediaPlayer* gameBgm;
    gameOver* showOver;

    vector <QTimer*> _attacktime;//炮台攻击频率
    vector <QGroupBox*> _groupBox;//选择界面 包括以下三个按钮
    vector <QPushButton*>  _levelUp;//升级按钮
    vector <QPushButton*> _newTower1;//建塔按钮
    vector <QPushButton*> _newTower2;
    vector <QPushButton*> _deleteTower;//拆塔按钮
    vector <QPushButton*> _towerBase;//塔基 点击后跳转到选择界面
    vector <QPushButton*> _return;
};

#endif // ENTERGAME_H
