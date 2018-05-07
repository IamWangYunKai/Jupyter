import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import ZSS 1.0 as ZSS

Window {
    id:control
    visible: true
    width: 500
    height: 500
    title: qsTr("Jupyter")
    property bool socketConnect : false;
    ZSS.Interaction{
        id : interaction;
    }
    Grid {
        id: settings;
        width: parent.width;
        padding:10;
        verticalItemAlignment: Grid.AlignVCenter;
        horizontalItemAlignment: Grid.AlignHCenter;
        spacing: 5;
        columns:1;
        property int itemWidth : width - 2*padding;
        ComboBox{
            id:networkInterfacesComboBox;
            enabled: !control.socketConnect;
            model:interaction.getNetworkInterfaces();
            onActivated: interaction.changeNetworkInterface(currentIndex);
            width:parent.itemWidth;
            function updateModel(){
                model = interaction.getNetworkInterfaces();
                if(currentIndex >= 0)
                    interaction.changeNetworkInterface(currentIndex);
            }
            Component.onCompleted: updateModel();
        }
        Button{
            width:parent.itemWidth;
            text:control.socketConnect ? "Disconnect" : "Connect";
            onClicked: {
                control.socketConnect = !control.socketConnect;
                if(!interaction.changeConnection(control.socketConnect)){
                    control.socketConnect = !control.socketConnect;
                }
            }
        }
        ComboBox{
            id:robotID;
            model: ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"];
            onActivated: interaction.changeRobotID(currentIndex);
            width:parent.itemWidth;
            function updateModel(){
                // = interaction.getNetworkInterfaces();
                if(currentIndex >= 0)
                    interaction.changeRobotID(currentIndex);
            }
            Component.onCompleted: updateModel();

        }
        RowLayout {
            id: textRowLayout
            TextField {
                id: sendText
                Layout.fillWidth: true
                focus: true
            }
            Button {
                text: 'Send'
                onClicked: {
                    interaction.send(sendText.text);
                }
            }
        }
    }
    MouseRectangle{
        id:r1;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        onValueChanged:{
            interaction.pos(x, y)
        }
    }
    MouseRectangle{
        id:r2;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        onValueChanged:{
            interaction.dir(x, y)
        }
    }

}
