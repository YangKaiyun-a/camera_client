#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#define sigManager SignalManager::instance()

#include <QObject>


class SignalManager : public QObject
{
    Q_OBJECT
public:
    explicit SignalManager(QObject *parent = nullptr);
    static SignalManager* instance();

signals:
    void connectSucceed(bool);          // TCP 客户端连接状态
    void openOrCloseCamera(bool);       // 打开或关闭摄像头
    void callQmlRefreshImg();           // 通知 QML 更新图片

private:
    static SignalManager* m_signalManager;

};

#endif // SIGNALMANAGER_H
