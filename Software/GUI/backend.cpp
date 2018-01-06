#include "backend.h"
#include <QThread>


Backend::Backend() {
    serial = new Serialport();
    parser = new Parser();
    timMsg = new QTimer(this);
    timer.start();
    timMsg->start(5000);

    connect(serial,SIGNAL(dataRecieved(QByteArray)),this,SLOT(dataRecieved(QByteArray)));
    connect(parser,SIGNAL(sAsyncMsg(unsigned int,float)),this,SLOT(slotAsyncMsg(unsigned int, float)));
    connect(parser,SIGNAL(sSyncMsg(unsigned int,float)),this,SLOT(slotSyncMsg(unsigned int, float)));
    connect(parser,SIGNAL(sReboot()),this,SLOT(slotReboot()));
    connect(timMsg,SIGNAL(timeout()),this,SLOT(slotDisconnected()));
    }

void Backend::setMotorPosition(double d)
{
    d = d*200;
    unsigned char pos =(unsigned char)d;
    //qDebug() << "SetSetPoint " << pos;

    if(timer.elapsed() > 100){
        this->sendMsg((unsigned char)SET_MASK, (unsigned char)MSG_ID::ID_MOTCTRL_POSITION, &pos);
        timer.restart();
    }
}

void Backend::setMode(bool b){
    qDebug() << "SetMode " << b;
    if(b){
       sendMsg((unsigned char)SET_MASK, (unsigned char)MSG_ID::ID_CONFIG, (unsigned int) CFG_AUTOMATIC);
    }else{
       sendMsg((unsigned char)SET_MASK, (unsigned char)MSG_ID::ID_CONFIG, (unsigned int) CFG_MANUAL);
    }
}

void Backend::setCalModeMotor(bool b){
    qDebug() << "setCalModeMotor " << b;
    sendMsg((unsigned char)SET_MASK, (unsigned char)MSG_ID::ID_CONFIG, (unsigned int) CFG_CAL_MOTOR);
}

void Backend::setCalModeController(bool b){
    qDebug() << "setCalModeController " << b;
    if(b){
        sendMsg((unsigned char)SET_MASK, (unsigned char)MSG_ID::ID_CONFIG, (unsigned int) CFG_CAL_CONTROLLER_ON);
    } else {
        sendMsg((unsigned char)SET_MASK, (unsigned char)MSG_ID::ID_CONFIG, (unsigned int) CFG_CAL_CONTROLLER_OFF);
    }

}

void Backend::setCalNorth(){
    sendMsg((unsigned char)SET_MASK, (unsigned char)MSG_ID::ID_CONFIG, (unsigned int) CFG_CAL_SETNORTH);
}

void Backend::dataRecieved(QByteArray data){
    //qDebug() << "Data arrived at Backend " << data << endl;
    parser->parse(data, data.length());
}

void Backend::connectBouy(QString port){
    qDebug() << "Connecting on: " <<  port << endl;
    serial->connect(port);
}

void Backend::slotAsyncMsg(unsigned int id, float value){
    //qDebug() << "slotAsyncMsg" << id << value << endl;
    timMsg->start(5000);
    emit this->sensorChange(id, value);
}

void Backend::slotSyncMsg(unsigned int id, float value){
    qDebug() << "slotSyncMsg" << id << value << endl;
    emit this->response(id, value);
}

void Backend::slotReboot(){
    emit this->reboot();
}

void Backend::sendCommandFromQML(int cmd,int id, QString data){

        this->sendMsg((unsigned char)cmd, (unsigned char)id, data.toFloat());
        qDebug() << cmd << " " << id << " " << data.toFloat() << endl;



}

void Backend::slotDisconnected(){
    emit this->sigDisconnected();
}

//void Backend::sendCommand(int cmd, int id, float data){
//    this->sendMsg((unsigned char)cmd, (unsigned char)id, (float)data);

//}
// send a float value
void Backend::sendMsg(unsigned char cmd, unsigned char id, float data){
    Msg msg;
    Payload payload;
    *(float*)&payload = data;
    msg.sot = SOP;
    msg.cmd = cmd;
    msg.id = id;
    msg.d  = payload;
    msg.crc = parser->CalcCRC((unsigned char*)&msg);

    QByteArray qMsg;
    qMsg.append((const char*) &msg, MSG_LEN);
    if(serial->sendData(qMsg)){
      parser->setLastSendID(id);
    }
}
// Send a unsigned integer
void Backend::sendMsg(unsigned char cmd, unsigned char id, unsigned int data){
    Msg msg;
    Payload payload;
    *(unsigned int*)&payload.c[0] = data;
    msg.sot = SOP;
    msg.cmd = cmd;
    msg.id = id;
    msg.d  = payload;
    msg.crc = parser->CalcCRC((unsigned char*)&msg);

    QByteArray qMsg;
    qMsg.append((const char*) &msg, MSG_LEN);
    if(serial->sendData(qMsg)){
      parser->setLastSendID(id);
    }
}

void Backend::sendMsg(unsigned char cmd, unsigned char id, unsigned char* data){
    Msg msg;
    Payload payload;
    payload.c[0] = *data;
    msg.sot = SOP;
    msg.cmd = cmd;
    msg.id = id;
    msg.d  = payload;
    msg.crc = parser->CalcCRC((unsigned char*)&msg);

    QByteArray qMsg;
    qMsg.append((const char*) &msg, MSG_LEN);
    if(serial->sendData(qMsg)){
      parser->setLastSendID(id);
    }
}




