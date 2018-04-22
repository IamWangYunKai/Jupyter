import QtQuick 2.10
import QtQuick.Window 2.0
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
Window {
    id:root;
    visible: true;
    width:300;
    height:600;
    //Material.theme: styleSwitch.checked ? Material.Dark : Material.Light
    ControlBoard{
        id:controlBoard;
        anchors.fill: parent;
    }
}
