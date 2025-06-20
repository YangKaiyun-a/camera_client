#include "registertoqml.h"
#include "signalmanager.h"
#include "datahandler.h"


#include <QQmlEngine>

RegisterToQml *RegisterToQml::m_registerToQml = nullptr;

RegisterToQml::RegisterToQml(QObject *parent)
    : QObject{parent}
{
    //初始化C++类
    sigManager;

    //注册C++类
    qmlRegisterSingletonInstance<DataHandler>("DataHandler", 1, 0, "DataHandler", DataHandler::getInstance());
}

RegisterToQml *RegisterToQml::getInstance()
{
    if(!m_registerToQml)
    {
        m_registerToQml = new RegisterToQml();
    }

    return m_registerToQml;
}
