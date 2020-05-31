#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(960,540);

    QIcon ico(":/picture/startGame.png");
    ui->startGame->setIcon(ico);
    ui->startGame->setIconSize(QSize(200,100));
    ui->startGame->setFlat(true);
    ui->startGame->setGeometry(380,360,200,100);

    connect(ui->startGame,SIGNAL(clicked()),this,SLOT(on_startGame_clicked()));
}
void MainWindow::paintEvent(QPaintEvent *){
    QPainter *painter;
    painter = new QPainter();
    painter->begin(this);
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->drawImage(0,0,QImage(":/picture/homePage.jpg"));
    painter->end();
    delete painter;
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_startGame_clicked(){
    this->hide();
    game_one.show();
}
