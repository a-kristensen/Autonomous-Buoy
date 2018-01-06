#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QtSerialPort/QSerialPort>

#define SOP 			0x96
#define MSG_LEN			8

typedef enum {
    WAIT_FOR_SOP = 1,
    RECIEVE_MSG = 2,
    HANDLE_MSG = 3
} RECV_STATE;

class Serialport : public QObject
{
    Q_OBJECT
public:
    explicit Serialport();
    int sendData(QByteArray data);
    void connect(QString port);

private slots:
    void serialRecieved();

signals:
     void dataRecieved(QByteArray);

private:
    QSerialPort *serialPort;
    QByteArray data;
    RECV_STATE recvState;
    char recvBytes;
};

#endif // SERIALPORT_H
