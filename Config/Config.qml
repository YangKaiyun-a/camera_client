pragma Singleton

import QtQuick
import DataHandler 1.0

Item {

    id: root

    /*******************************变量*********************************/


    // 是否打开摄像头
    property bool isOpenCamera: false



    /*******************************信号*********************************/


    //设备按钮点击信号
    signal sigDeviceButtonClicked(int deviceId);

    //日志返回主页面信号
    signal sigLogReturnToActionsPage();



    /*******************************函数*********************************/

    //发送设备按钮点击信号
    function emitSigDeviceButtonClicked(deviceId) {
        sigDeviceButtonClicked(deviceId)
    }

    function openCameraButtonClicked(isOpenCamera) {
        if(isOpenCamera) {
            console.log(qsTr("打开摄像头"))
        } else {
            console.log(qsTr("关闭摄像头"))
        }

        DataHandler.openCamera(isOpenCamera)
    }





    /************************************** can接口 **************************************/


    //下发can指令
    function executeCommand(deviceId, commandStr, rdmlJson) {

        var commandType = Config.CommandTypeNum.RESET

        if(commandStr === "复位") {
            commandType = Config.CommandTypeNum.RESET
        } else if(commandStr === "开盖") {
            commandType = Config.CommandTypeNum.LID_OPEN
        } else if(commandStr === "关盖") {
            commandType = Config.CommandTypeNum.LID_CLOSE
        } else if(commandStr === "发送方案") {
            commandType = Config.CommandTypeNum.SET_RDML
        } else if(commandStr === "开始") {
            commandType = Config.CommandTypeNum.START
        } else if(commandStr === "停止") {
            commandType = Config.CommandTypeNum.STOP
        } else if(commandStr === "温度") {
            commandType = Config.CommandTypeNum.TEMPERATURE
        } else if(commandStr === "设置参数") {
            commandType = Config.CommandTypeNum.SET_PARAM
        } else if(commandStr === "获取参数") {
            commandType = Config.CommandTypeNum.READ_PARAM
        }

        console.log("deviceId: ", deviceId, ", 执行动作：", commandStr)
        DataHandler.sendCommand(deviceId, commandType, rdmlJson)
    }

    //读取单个PCR温度
    function getTemperature(deviceCanId) {
        executeCommand(deviceCanId, "温度", "")
    }
}
