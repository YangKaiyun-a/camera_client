#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QImage>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient(QObject *parent = nullptr);
    ~TcpClient();

    static TcpClient *instance();

    void connectToServer(const QHostAddress &address, quint16 port);
    void sendStartCameraRequest(bool command);  // 向服务端发送启动摄像头请求


private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QTcpSocket::SocketError socketError);
    void onOpenOrCloseCamera(bool command);


private:
    QTcpSocket *m_socket = nullptr;
    static TcpClient* m_client;
    quint32 m_expectedLen = 0;  // 每次接收的图片长度
    QImage m_image;             // 每次接收的图片
    QByteArray m_buf;
};

#endif // TCPCLIENT_H
