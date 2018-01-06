#include "serialport.h"
#include <QDebug>

Serialport::Serialport()
{
    qDebug() << " Serial port constructed" << endl;
    recvState = WAIT_FOR_SOP;

    serialPort = new QSerialPort();
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

}

void Serialport::serialRecieved(){
    //QByteArray data = serialPort->read(8);
    //qDebug() << "old method :" << data << endl;
    unsigned char *rx;
    char srx;
    qint64 bytes = serialPort->bytesAvailable();
    //qDebug() << bytes << " bytes recieved" << endl;
    for(int i = 0; i < bytes; i++){
        if(serialPort->getChar(&srx)){
            switch(recvState){
                case WAIT_FOR_SOP:
                    rx = ((unsigned char*)((void*)&srx));
                    if(*rx == SOP){
                        //qDebug() << "SOP recieved" << endl;
                        data.append(srx);
                        recvState = RECIEVE_MSG;
                        recvBytes = 1;
                    } else {
                        qDebug() << "Not SOP, recieved" << *rx << endl;
                    }
                break;

                case RECIEVE_MSG:
                    if(recvBytes < MSG_LEN-1){
                        data.append(srx);
                        recvBytes++;
                        //qDebug() << "Appending" << endl;
                    } else { // last byte
                        data.append(srx);
                        //qDebug() << "Emitting: " << data << data.length() << endl;
                        emit dataRecieved(data);
                        data.clear();
                        recvState = WAIT_FOR_SOP;
                    }
                break;
            }
        } else {
            qDebug() << "Could not read char" << serialPort->error() << endl;
        }


    }

    //emit dataRecieved(data);


}

int Serialport::sendData(QByteArray data){
    //QByteArray temp;
    //temp = temp.append(data);
    if(serialPort->write(data) < data.length()){
        qDebug() << "Data not written" << data << endl;
        return -1;
    } else {
        qDebug() << "Data written: " << data << endl;
        return 1;
    }
}

void Serialport::connect(QString port){
    serialPort->setPortName(port);
    if(serialPort->open(QSerialPort::ReadWrite))
    {
        qDebug() << "Connected" << endl;
        QObject::connect(serialPort,SIGNAL(readyRead()),this, SLOT(serialRecieved()));
    } else {
        qDebug() << "Failed to open Port" << serialPort->error() << endl;
    }

}
