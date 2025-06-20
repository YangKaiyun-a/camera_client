import QtQuick
import QtQuick.Controls
import QtMultimedia
import QtQml
import Config
import DataHandler 1.0

ApplicationWindow {
    width: 1500
    height: 800
    visible: true
    title: qsTr("因特尔相机采集器")

    Connections {
        target: DataHandler

        function onCallQmlRefreshImg() {
            camera_image.source = "image://live/" + Math.random()
        }
    }

    Image {
        id: camera_image
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        source: "image://live/any"
    }


    Button {
        id: btnOpenCamera
        text: Config.isOpenCamera ? "关闭摄像头" : "开启摄像头"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: camera_image.bottom
        anchors.bottom: parent.bottom
        onClicked: {
            Config.openCameraButtonClicked(!Config.isOpenCamera)
            Config.isOpenCamera = !Config.isOpenCamera
        }
    }
}
