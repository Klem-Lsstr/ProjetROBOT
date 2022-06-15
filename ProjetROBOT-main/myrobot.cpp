#include "myrobot.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}



//hUSB is the serial port handle opened at 19200 baud
void MyRobot::SetRobot1( short speed1,short speed2,unsigned char SpeedFlag)
{


    DataToSend[0] = (unsigned char)255;
    DataToSend[1] = 0x07;
    DataToSend[2] = speed1;
    DataToSend[3] = 0;
    DataToSend[4] = speed2;
    DataToSend[5] = 0;
    DataToSend[6] = SpeedFlag;




    unsigned short crc = this->Crc16(DataToSend  , 7 );
    //qDebug() << (unsigned short)crc ;


    DataToSend[7] = (unsigned char)crc;
    DataToSend[8] =  (unsigned char)(crc >> 8);

}

short MyRobot::VitesseFromRobot(){

    QDataStream socketstream(socket);
    quint8 battery,speedFrontL, speedRearL,speedFrontR,speedRearR,IrLeft, IrRight;
    socketstream>>battery>>speedFrontL>>speedRearL>>speedFrontR>>speedRearR>>IrLeft>>IrRight;
    MyRobot::Sensors sensors;
    sensors.battery=battery;
    sensors.speedLeft=speedFrontL/2 + speedRearL/2;
    sensors.speedRight=speedFrontR/2 + speedRearR/2;
    sensors.adc4=IrLeft;
    sensors.adc0=IrRight;

    emit sensorsUpdate(sensors);



}



unsigned short MyRobot::Crc16(QByteArray tableau , unsigned char Taille_max)
{
unsigned int Crc = 0xFFFF;
unsigned int Polynome = 0xA001;
unsigned int CptOctet = 0;
unsigned int CptBit = 0;
unsigned int Parity= 0;
 Crc = 0xFFFF;
 Polynome = 0xA001;
for ( CptOctet= 1 ; CptOctet < Taille_max ; CptOctet++)
 {
 Crc ^= (unsigned char)tableau[CptOctet];
 for ( CptBit = 0; CptBit <= 7 ; CptBit++)
 {
 Parity= Crc;
 Crc >>= 1;
 if (Parity%2 == true) Crc ^= Polynome;
 }
 }
return(Crc);
}


