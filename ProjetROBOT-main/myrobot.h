#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <iostream>
#include <QDataStream>



class MyRobot : public QObject {
    Q_OBJECT
public:

    class Sensors {
        public:
            Sensors():speedLeft(0),speedRight(0),odoLeft(0),odoRight(0),battery(0),current(0),adc0(0),adc1(0),adc3(0),adc4(0){}
            float speedLeft;
            float speedRight;
            float odoLeft;
            float odoRight;
            float battery;
            float current;
            float adc0;
            float adc1;
            float adc3;
            float adc4;
        };


    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
    void SetRobot1(short speed1,short speed2,unsigned char SpeedFlag);
    unsigned short Crc16(QByteArray tableau , unsigned char Taille_max);
    short VitesseFromRobot();

signals:
    void updateUI(const QByteArray Data);
    void sensorsUpdate(MyRobot::Sensors sensorsValue);
public slots:

    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
};

#endif // MYROBOT_H
