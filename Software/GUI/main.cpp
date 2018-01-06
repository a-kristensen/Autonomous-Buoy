#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "backend.h"
#include <QQmlContext>
#include <QDebug>

#include <QtSerialPort/QSerialPort>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Backend *backend = new Backend();
    //Test test;
    QQmlApplicationEngine* e = new QQmlApplicationEngine();
    e->rootContext()->setContextProperty("backend", backend);

    e->load(QUrl(QLatin1String("qrc:/main.qml")));
    if (e->rootObjects().isEmpty())
        return -1;

    //get first rootobject in the list and cast to quickwindow
    QObject * topLevel = e->rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow*>(topLevel);
    QObject::connect(backend, SIGNAL(sensorChange(QVariant, QVariant)), window, SLOT(sensorChange(QVariant, QVariant)));
    QObject::connect(backend, SIGNAL(response(QVariant, QVariant)), window, SLOT(response(QVariant, QVariant)));
    QObject::connect(backend, SIGNAL(reboot()), window, SLOT(reboot()));
    QObject::connect(backend, SIGNAL(sigDisconnected()), window, SLOT(disconnected()));



    return app.exec();
}
