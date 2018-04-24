#include "communicator.h"
#include "staticparam.h"
#include <QNetworkInterface>
#include <QtMath>
#include <QTimer>
#include "proto/zss_cmd.pb.h"

Communicator::Communicator(QObject *parent) : QObject(parent){
    QObject::connect(&receiveSocket,SIGNAL(readyRead()),this,SLOT(testReceive()),Qt::DirectConnection);
    QTimer *timer = new QTimer(this);
    QTimer::connect(timer, SIGNAL(timeout()), this, SLOT(sendCommand()));
    timer->start(16);
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
    QByteArray data = message.toLatin1();
    //qDebug() << "try to send : " << data.toHex();
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

void Communicator::sendCommand(){
    ZSS::Protocol::Robots_Command commands;
    auto command = commands.add_command();
    command->set_robot_id(1);
    command->set_velocity_x(vy);
    command->set_velocity_y(vx);//??????????
    command->set_velocity_r(vr);
    //qDebug() <<"vx:" << vx <<" vy:"<<vy<<" vr:"<<vr;
    int size = commands.ByteSize();
    QByteArray buffer(size,0);
    commands.SerializeToArray(buffer.data(), size);
    sendSocket.writeDatagram(buffer,QHostAddress(ZSS::Jupyter::UDP_ADDRESS),ZSS::Jupyter::UDP_SEND_PORT);
}

void Communicator::pos(int x, int y){
    y = -y;
    last_vx = vx;
    last_vy = vy;
    vx = ZSS::Vehicle::MAX_SPEED * x / 100.0;
    vy = ZSS::Vehicle::MAX_SPEED * y / 100.0;
    if (vx*vx + vy*vy > ZSS::Vehicle::MAX_SPEED*ZSS::Vehicle::MAX_SPEED){
        float theta = qAtan2(-y, x);
        //qDebug() << "theta: "<<theta;
        vx = ZSS::Vehicle::MAX_SPEED*cos(theta);
        vy =- ZSS::Vehicle::MAX_SPEED*sin(theta);
    }
    qDebug() << "Vel:" << vx<<", " << vy;
    qDebug() <<"x: " <<x << "y: "<< y;
}

void Communicator::dir(int x, int y){
    last_vr = vr;
    vr = M_PI - abs(qAtan2(x, y));
    if (x < 0) vr = - vr;
    vr = ZSS::Vehicle::MAX_ROTATION_SPEED * sin(vr);
    if (abs(vr) < 0.01) vr = 0;
    qDebug() << "Dir:" << vr;
}
