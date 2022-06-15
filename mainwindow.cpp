#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    robot.doConnect();

    QWebEngineView *page = ui->CAM;
    page->load(QUrl("http://192.168.1.106:8080/?action=stream"));

    //page->load(QUrl("http://158.58.130.148/mjpg/video.mjpg"));
    manager = new QNetworkAccessManager();
    ui->INFO->setText(QString(robot.DataReceived[2]));


    connect(robot.getSocket(), SIGNAL(connected()),this, SLOT(AfficheVitesse()));


    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::lightGray);
    setPalette(pal);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::AfficheVitesse(){


    short V1 = robot.DataReceived[0]/2448/20*0.44;
    short V2 = robot.DataReceived[9]/2448/20*0.44;
    ui->Vitesse1->setText(QString(V1));

    ui->Vitesse2->setText(QString(V2));
    qDebug()<<V1;

}

//Fonction connexion
void MainWindow::on_ButConnect_pressed(){
    robot.doConnect();



}

//Fonction deconnexion
void MainWindow::on_ButDisconnect_pressed(){

    robot.disConnect();

}


//Bouton Avancer
void MainWindow::on_ButUp_pressed()
{

    robot.SetRobot1(100,100,80);
    //Mouvement=true;

}


void MainWindow::on_ButUp_released()
{

    robot.SetRobot1(0,0,80);
    //Mouvement=false;
}

//Bouton Droite
void MainWindow::on_ButRight_pressed()
{

    robot.SetRobot1(100,15,80);
    //Mouvement=true;
}


void MainWindow::on_ButRight_released()
{

    robot.SetRobot1(0,0,80);
    //Mouvement=false;
}

//Bouton Reculer
void MainWindow::on_ButDown_pressed()
{

    robot.SetRobot1(100,100,0);
    //Mouvement=true;
}


void MainWindow::on_ButDown_released()
{

    robot.SetRobot1(0,0,0);
    //Mouvement=false;
}

//Bouton Gauche
void MainWindow::on_ButLeft_pressed()
{

    robot.SetRobot1(15,100,80);
    //Mouvement=true;
}


void MainWindow::on_ButLeft_released()
{

    robot.SetRobot1(0,0,80);
    //Mouvement=false;
}



void MainWindow::on_CAM_DOWN_pressed()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200"));
        manager->get(request);
}


void MainWindow::on_CAM_RIGHT_pressed()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200"));
            manager->get(request);
}


void MainWindow::on_CAM_UP_pressed()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200"));
        manager->get(request);
}


void MainWindow::on_CAM_LEFT_pressed()
{
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200"));
            manager->get(request);
}



