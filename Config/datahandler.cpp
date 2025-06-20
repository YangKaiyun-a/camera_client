#include "datahandler.h"

#include <QCoreApplication>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

DataHandler* DataHandler::m_dataHandler = nullptr;

DataHandler::DataHandler(QObject *parent)
    : QObject{parent}
{
    init();
}


/***************************正常函数***************************/

void DataHandler::init()
{
    initConnect();
}

void DataHandler::initConnect()
{
    connect(sigManager, &SignalManager::callQmlRefreshImg, this, &DataHandler::onCallQmlRefreshImg);
}

DataHandler *DataHandler::getInstance()
{
    if(!m_dataHandler)
    {
        m_dataHandler = new DataHandler();
    }

    return m_dataHandler;
}




/***************************QML接口函数***************************/

// 打开/关闭摄像头
void DataHandler::openCamera(bool command)
{
    Q_EMIT sigManager->openOrCloseCamera(command);
}









/***************************槽函数***************************/

void DataHandler::onCallQmlRefreshImg()
{
    Q_EMIT callQmlRefreshImg();
}
