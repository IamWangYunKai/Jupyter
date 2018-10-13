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
        isConnect = true;
        return true;
    }
    disconnect();
    return false;
}
bool Communicator::disconnect(){
    receiveSocket.disconnectFromHost();
    sendSocket.disconnectFromHost();
    isConnect = false;
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

void Communicator::changeRobotID(int index){
    robotID = index;
}
// test TODO;
bool Communicator::testSend(const QString& message){
    //qDebug() << "try to send : " << message;
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
        //qDebug() << "receive data : " << datagram;
    }
}

void Communicator::sendCommand(){
    plan_pos();
    plan_dir();
    if(isConnect==true){
        qDebug()<< "robotID:"<<robotID<<"vx: "<<vx <<" vy: "<<vy << " vr:"<<vr;
        ZSS::Protocol::Robots_Command commands;
        auto command = commands.add_command();
        command->set_robot_id(robotID);
        command->set_velocity_x(vy);
        command->set_velocity_y(vx);//坐标问题
        command->set_velocity_r(vr);
        command->set_kick(false);//////
        command->set_power(0);//////
        command->set_dribbler_spin(0);//////
        int size = commands.ByteSize();
        QByteArray buffer(size,0);
        commands.SerializeToArray(buffer.data(), size);
        sendSocket.writeDatagram(buffer,QHostAddress(ZSS::Jupyter::UDP_ADDRESS),ZSS::Jupyter::UDP_SEND_PORT);
        //qDebug()<<buffer;
    }
}

void Communicator::pos(int x, int y){
    y = -y;
    _vx = ZSS::Vehicle::MAX_SPEED * x / 100.0;
    _vy = ZSS::Vehicle::MAX_SPEED * y / 100.0;
    if (_vx*_vx + _vy*_vy > ZSS::Vehicle::MAX_SPEED*ZSS::Vehicle::MAX_SPEED){
        float theta = qAtan2(-y, x);
        //qDebug() << "theta: "<<theta;
        _vx = ZSS::Vehicle::MAX_SPEED*cos(theta);
        _vy =- ZSS::Vehicle::MAX_SPEED*sin(theta);
    }
    //qDebug() << "Vel:" << vx<<", " << vy;
}

void Communicator::dir(int x, int y){
    _vr = M_PI - abs(qAtan2(x, y));
    if (x < 0) _vr = - _vr;
    _vr = ZSS::Vehicle::MAX_ROTATION_SPEED * sin(_vr);
    if (abs(_vr) < 0.01) _vr = 0.0;
    //qDebug() << "Dir:" << _vr;
}

void Communicator::plan_pos(){
    float dvx = _vx - vx;
    float dvy = _vy - vy;
    float acc = sqrt(dvx*dvx + dvy*dvy);
    if (60.0 * acc > ZSS::Vehicle::MAX_ACC){
        vx = vx + ZSS::Vehicle::MAX_ACC * (dvx/acc) / 60.0;
        vy = vy + ZSS::Vehicle::MAX_ACC * (dvy/acc) / 60.0;
    }
    else{
        vx = _vx;
        vy = _vy;
    }
}

void Communicator::plan_dir(){
    float dvr = _vr - vr;
    if (60.0 * abs(dvr) > ZSS::Vehicle::MAX_ROTATION_ACC){
        vr = vr + ZSS::Vehicle::MAX_ROTATION_ACC * (dvr/abs(dvr)) / 60.0;
    }
    else{
        vr = _vr;
    }
}
