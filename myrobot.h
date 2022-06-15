#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <iostream>


class MyRobot : public QObject {
    Q_OBJECT
public:
    QTcpSocket* getSocket();
    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
    void SetRobot1(short speed1,short speed2,unsigned char SpeedFlag);
    unsigned short Crc16(QByteArray tableau , unsigned char Taille_max);
    short VitesseFromRobot1();
    short VitesseFromRobot2();

signals:
    void updateUI(const QByteArray Data);
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

