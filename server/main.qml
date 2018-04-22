import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import ZSS 1.0 as ZSS
Window {
    id:control
    visible: true
    width: 400
    height: 480
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

}
