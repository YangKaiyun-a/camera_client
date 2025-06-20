#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Config/registertoqml.h"
#include "Controller/tcpclient.h"
#include "Controller/myimageprovider.h"

const QString SERVERADDRESS = "10.9.28.204";
const int SERVERPORT = 1234;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 注册 C++ 类
    RegisterToQml::getInstance();

    // 初始化 TCP 客户端
    TcpClient::instance()->connectToServer(QHostAddress(SERVERADDRESS), SERVERPORT);

    QQmlApplicationEngine engine;

    // 初始化 MyImageProvider
    engine.addImageProvider("live", MyImageProvider::getInstance());
    MyImageProvider::getInstance()->setImage(QImage("F:/111.png"));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("camera", "Main");

    return app.exec();
}
