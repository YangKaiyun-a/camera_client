#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include "signalmanager.h"

#include <QObject>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrentRun>
#include <QVariant>

class DataHandler : public QObject
{
    Q_OBJECT
public:
    explicit DataHandler(QObject *parent = nullptr);
    void init();
    void initConnect();
    static DataHandler *getInstance();

    /***************************QML接口函数***************************/

    // 打开/关闭摄像头
    Q_INVOKABLE void openCamera(bool command);


    /***************************正常函数***************************/


signals:
    void callQmlRefreshImg();

private slots:
    void onCallQmlRefreshImg();


private:
    static DataHandler* m_dataHandler;

};

#endif // DATAHANDLER_H
