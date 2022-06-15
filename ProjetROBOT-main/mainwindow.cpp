#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    robot.doConnect();
    QWebEngineView *cam = ui->CAM;
    cam->load(QUrl("http://192.168.1.106:8080/?action=stream"));

    manager = new QNetworkAccessManager();


    connect(&robot,SIGNAL(updateUI(QByteArray)),this,SLOT(AfficheVitesse(QByteArray)));
    //connect(&robot,SIGNAL(sensorsUpdate(MyRobot::Sensors sensorsValue)),this,SLOT(displaySensorsValues(MyRobot::Sensors sensors)));

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(185);

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::lightGray);
    setPalette(pal);

}



void MainWindow::displaySensorsValues(MyRobot::Sensors sensors){
    //ui->LCDBaterie->display(sensors.battery);
    //ui->LCDCurrent->display(sensors.current);
    ui->V1->display(sensors.speedLeft);
    ui->V2->display(sensors.speedRight);

}



MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::AfficheVitesse(const QByteArray Data){




    ui->IR1->display((unsigned char)Data[3]);
    ui->IR3->display((unsigned char)Data[4]);
    ui->IR2->display((unsigned char)Data[11]);
    ui->IR4->display((unsigned char)Data[12]);
    ui->progressBar->setValue((unsigned char)Data[2]);

    unsigned long V = ((long)Data[8]<<24) + ((long)Data[7]<<16) + ((long)Data[6]<<8) + (long)Data[5];
    unsigned long V1 = V - PV1;
    PV1 = V;
    V1 = (V1/2448)*20*0.44;
    ui->V1->display((unsigned char)V1);

    unsigned long VB2 = ((long)Data[8]<<24) + ((long)Data[7]<<16) + ((long)Data[6]<<8) + (long)Data[5];
    unsigned long V2 = VB2 - PV2;
    PV2 = VB2;
    V2 = (V2/2448)*20*0.44;
    ui->V2->display((unsigned char)V2);
    ui->ACTV->setText("Connecté");




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

    if(ui->ButUp->isDown()){
    robot.SetRobot1(100,100,80);
    }
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



