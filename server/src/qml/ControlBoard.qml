import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import ZSS 1.0 as ZSS
Page{
    id:control;
    property bool socketConnect : false;//
    ZSS.Interaction{
        id:interaction;
    }
    ZSS.Test{
        id:test;
    }

    header:TabBar {
        id: bar
        width:parent.width;
        contentHeight:80;
        height:contentHeight;
        position: TabBar.Header;
        TabButton {
            icon.source:"/source/radio.png";
        }
        TabButton {
            icon.source:"/source/settings.png";
        }
    }
    Timer{
        id:oneSecond;
        interval:1000;
        running:true;
        repeat:true;
        onTriggered: {
            radioComboBox.updateModel();
        }
    }
    property bool radioConnect : false;
    StackLayout {
        id:controlLayout;
        width: parent.width;
        height:parent.height;
        currentIndex: bar.currentIndex;
        Grid {
            id: radio;
            width: parent.width;
            padding:10;
            verticalItemAlignment: Grid.AlignVCenter;
            horizontalItemAlignment: Grid.AlignHCenter;
            spacing: 0;
            columns:1;
            property int itemWidth : width - 2*padding;
            GroupBox{
                width:parent.itemWidth;
                Grid{
                    width:parent.width;
                    verticalItemAlignment: Grid.AlignVCenter;
                    horizontalItemAlignment: Grid.AlignHCenter;
                    spacing: 0;
                    columns:1;
                    property int itemWidth : width - 2*padding;
                    SpinBox{
                        width:parent.itemWidth;
                        from:0;to:15;
                        wrap:true;
                        value:interaction.getFrequency();
                        onValueModified: {
                            if(!interaction.changeSerialFrequency(value))
                                value:interaction.getFrequency();
                        }
                    }
                    ComboBox{
                        id:radioComboBox;
                        enabled: !control.radioConnect;
                        model:interaction.getSerialPortsList();
                        onActivated: interaction.changeSerialPort(currentIndex);
                        width:parent.itemWidth;
                        function updateModel(){
                            model = interaction.getSerialPortsList();
                            if(currentIndex >= 0)
                                interaction.changeSerialPort(currentIndex);
                        }
                        Component.onCompleted: updateModel();
                    }
                    Button{
                        width:parent.itemWidth;
                        icon.source:control.radioConnect ? "/source/connect.png" : "/source/disconnect.png";
                        onClicked: {
                            control.radioConnect = !control.radioConnect;
                            if(!interaction.connectSerialPort(control.radioConnect)){
                                control.radioConnect = !control.radioConnect;
                            }
                        }
                    }
                }
            }
            Button{
                width:parent.itemWidth;
                text: "test actionmodule";
                onClicked: {
                    test.testAM();
                }
            }
        /*****************************************/
        /*                  UDP                 */
       /*****************************************/
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
        /*****************************************/
        }
        Settings{
            anchors.fill: parent;
        }
    }
}
