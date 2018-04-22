#include "communicator.h"
#include "staticparam.h"
#include <QNetworkInterface>
#include "proto/zss_cmd.pb.h"

Communicator::Communicator(QObject *parent) : QObject(parent){
    QObject::connect(&receiveSocket,SIGNAL(readyRead()),this,SLOT(testReceive()),Qt::DirectConnection);
}
bool Communicator::connect(){
    if (
            receiveSocket.bind(QHostAddress::AnyIPv4,ZSS::Jupyter::UDP_RECEIVE_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint) &&
            receiveSocket.joinMulticastGroup(QHostAddress(ZSS::Jupyter::UDP_ADDRESS),QNetworkInterface::interfaceFromName(networkInterfaceNames[networkInterfaceIndex]))
            ){
        sendSocket.setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
        return true;
    }
    disconnect();
    return false;
}
bool Communicator::disconnect(){
    receiveSocket.disconnectFromHost();
    sendSocket.disconnectFromHost();
    return true;
}
QStringList& Communicator::updateNetworkInterfaces(){
    const auto& interfaces = QNetworkInterface::allInterfaces();
    networkInterfaceNames.clear();
    networkInterfaceReadableNames.clear();
    for(int i = 0; i < interfaces.length(); ++i){
        networkInterfaceNames.append(interfaces[i].name());
        networkInterfaceReadableNames.append(interfaces[i].humanReadableName());
    }
    return networkInterfaceReadableNames;
}
void Communicator::changeNetworkInterface(int index){
    networkInterfaceIndex = index;
}
// test TODO;
bool Communicator::testSend(const QString& message){
    qDebug() << "try to send : " << message;
    //QByteArray data = message.toLatin1();
    QByteArray data = sendCommand();
    sendSocket.writeDatagram(data,QHostAddress(ZSS::Jupyter::UDP_ADDRESS),ZSS::Jupyter::UDP_SEND_PORT);
    return true;
}
void Communicator::testReceive(){
    QByteArray datagram;
    while (receiveSocket.state() == QUdpSocket::BoundState && receiveSocket.hasPendingDatagrams()) {
        datagram.resize(receiveSocket.pendingDatagramSize());
        receiveSocket.readDatagram(datagram.data(), datagram.size());
        qDebug() << "receive data : " << datagram;
    }
}

QByteArray Communicator::sendCommand(){
    ZSS::Protocol::Robots_Command commands;
    auto command = commands.add_command();
    command->set_robot_id(1);
    command->set_velocity_x(0.2);
    int size = commands.ByteSize();
    QByteArray buffer(size,0);
    commands.SerializeToArray(buffer.data(), size);
    return buffer;
}
