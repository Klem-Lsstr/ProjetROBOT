#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myrobot.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QWebEngineView>
#include <QNetworkAccessManager>
#include <QDataStream>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MyRobot robot;
    bool Mouvement = false;
    void KeyPressEvent(QKeyEvent *e);
    void KeyReleaseEvent(QKeyEvent *e);


//Boutons interface graphique
private slots:
    void displaySensorsValues(MyRobot::Sensors sensors);
    void AfficheVitesse(const QByteArray Data);
    //Boutons directions
    void on_ButUp_pressed();
    void on_ButUp_released();
    void on_ButRight_pressed();
    void on_ButRight_released();
    void on_ButDown_pressed();
    void on_ButDown_released();
    void on_ButLeft_pressed();
    void on_ButLeft_released();

    //Boutons connexion
    void on_ButConnect_pressed();
    void on_ButDisconnect_pressed();


    void on_CAM_DOWN_pressed();

    void on_CAM_RIGHT_pressed();

    void on_CAM_UP_pressed();

    void on_CAM_LEFT_pressed();


private:
    long PV1 = 0;
    long PV2 = 0;
    int nb;
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
};
#endif // MAINWINDOW_H
