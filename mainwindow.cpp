#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(960,540);

    QIcon ico(":/picture/version_easy.png");
    ui->version_easy->setIcon(ico);
    ui->version_easy->setIconSize(QSize(200,100));
    ui->version_easy->setFlat(true);
    ui->version_easy->setGeometry(380,300,200,100);

    QIcon ico2(":/picture/version_hard.png");
    ui->version_hard->setIcon(ico2);
    ui->version_hard->setIconSize(QSize(200,100));
    ui->version_hard->setFlat(true);
    ui->version_hard->setGeometry(380,400,200,100);

    connect(ui->version_easy,SIGNAL(clicked()),this,SLOT(on_version_easy_clicked()));
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
void MainWindow::on_version_easy_clicked()
{
    this->hide();
    game_one.show();
}
