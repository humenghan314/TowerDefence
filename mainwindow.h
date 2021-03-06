#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "world.h"
#include "entergame.h"
#include <QTimer>
#include <QPainter>
#include <QPushButton>
#include <QMultimedia>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
protected slots:
    void on_version_easy_clicked();
    void on_version_hard_clicked();
private:
    Ui::MainWindow *ui;
    enterGame * game_one;
    enterGame * game_two;
    QMediaPlayer * music;
};

#endif // MAINWINDOW_H
