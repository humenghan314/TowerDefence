#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QImage>

namespace Ui {
class gameOver;
}

class gameOver : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameOver(QWidget *parent = 0);
    ~gameOver();
    void setImage(QImage ima){showGameOver=ima;}
    void paintEvent(QPaintEvent *);
signals:
    void myReturnSignal();
protected slots:
    void click_GameReturn();
private:
    Ui::gameOver *ui;
    QPushButton* GameReturn;
    QImage showGameOver;
};

#endif // GAMEOVER_H
