#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QDebug>
#include "serialport.h"
#include "parser.h"
#include <QElapsedTimer>
#include <QTimer>


class Backend : public QObject
{
        Q_OBJECT
public:

    explicit Backend();
    Q_INVOKABLE void setMotorPosition(double);
    Q_INVOKABLE void setMode(bool);
    Q_INVOKABLE void connectBouy(QString port);
    Q_INVOKABLE void sendCommandFromQML(int cmd,int id, QString data);
    Q_INVOKABLE void setCalModeMotor(bool b);
    Q_INVOKABLE void setCalModeController(bool b);
    Q_INVOKABLE void setCalNorth();
    //Q_INVOKABLE void sendCommand(int cmd, int id, float data);
    void sendMsg(unsigned char cmd, unsigned char id, float data);
    void sendMsg(unsigned char cmd, unsigned char id, unsigned int data);
    void sendMsg(unsigned char cmd, unsigned char id, unsigned char* data);

signals:
    void sensorChange(QVariant id, QVariant value);
    void response(QVariant id, QVariant value);
    void reboot();
    void sigDisconnected();
public slots:
    void dataRecieved(QByteArray data);
    void slotAsyncMsg(unsigned int id, float value);
    void slotSyncMsg(unsigned int id, float value);
    void slotReboot();
    void slotDisconnected();

private:
    Serialport *serial = NULL;
    Parser *parser = NULL;
    QElapsedTimer timer;
    QTimer *timMsg;
};

#endif // BACKEND_H
//

#ifndef BACKEND_H
#define BACKEND_H

#endif // BACKEND_H
