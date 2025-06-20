#include "tcpclient.h"
#include "signalmanager.h"
#include "myimageprovider.h"

#include <QDebug>
#include <QNetworkProxy>
#include <winsock2.h>
#include <ws2tcpip.h>

TcpClient *TcpClient::m_client =  nullptr;



TcpClient::TcpClient(QObject *parent) : QObject{parent}
{
    m_socket = new QTcpSocket(this);
    m_socket->setProxy(QNetworkProxy::NoProxy);

    connect(m_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(m_socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
    connect(sigManager, &SignalManager::openOrCloseCamera, this, &TcpClient::onOpenOrCloseCamera);

    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0)
    {
        //处理错误
    }
}

TcpClient::~TcpClient()
{
    WSACleanup();
}

TcpClient *TcpClient::instance()
{
    if(nullptr == m_client)
    {
        m_client   = new TcpClient();
    }

    return m_client;
}

void TcpClient::connectToServer(const QHostAddress &address, quint16 port)
{
    qDebug() << "连接服务器 " << address << ":" << port;
    m_socket->connectToHost(address, port);
}

void TcpClient::sendStartCameraRequest(bool command)
{
    const char* msg = command ? "START_CAMERA" : "STOP_CAMERA";

    qDebug() << msg;

    if (m_socket->state() == QTcpSocket::ConnectedState)
    {
        m_socket->write(msg);
        m_socket->flush();
    }
    else
    {
        qDebug() << "发送指令失败，未连接";
    }
}

/***********************************槽函数***********************************/

void TcpClient::onConnected()
{
    Q_EMIT sigManager->connectSucceed(true);
    qDebug() << "连接成功";
}

void TcpClient::onReadyRead()
{
    while (m_socket->bytesAvailable() > 0)
    {
        // 收长度 4B
        if (m_expectedLen == 0 && m_socket->bytesAvailable() >= 4)
        {
            QByteArray lenBytes = m_socket->read(4);
            memcpy(&m_expectedLen, lenBytes.constData(), 4);
            m_expectedLen = ntohl(m_expectedLen);
        }

        // 收图片数据
        if (m_expectedLen > 0 && m_socket->bytesAvailable() >= m_expectedLen)
        {
            QByteArray imgData = m_socket->read(m_expectedLen);
            QImage img;
            img.loadFromData(imgData, "JPG");
            if (!img.isNull())
            {
                m_image = img;

                // 更新 provider 图像
                MyImageProvider::getInstance()->setImage(m_image);

                // 更新 QML 图像
                Q_EMIT sigManager->callQmlRefreshImg();
            }
            m_expectedLen = 0; // 收完重置，等待下一帧
        }
        else
        {
            break; // 数据不够，等下一轮
        }
    }
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    Q_EMIT sigManager->connectSucceed(false);
    qDebug() << "连接失败:" << m_socket->errorString();
}

void TcpClient::onOpenOrCloseCamera(bool command)
{
    sendStartCameraRequest(command);
}
