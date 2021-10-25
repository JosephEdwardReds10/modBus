#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>

#include "host.h"
#include "socket.h"
#include "server.h"
#include "idevice.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);





//    QThread workerThread;
//    workerThread.setObjectName("Thread::Server");
//    Server *worker = new Server();
//    worker->moveToThread(&workerThread);
//    QObject::connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
//    QObject::connect(&workerThread, &QThread::started, worker, &Server::run);
//    workerThread.start();

    qmlRegisterType<Host>("UTTEC" , 1 , 0 , "Host");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
