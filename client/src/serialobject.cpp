#include <QtSerialPort/QSerialPortInfo>
#include "serialobject.h"
SerialObject::SerialObject(QObject *parent):QObject(parent),radioPacket(&serial){
    // add needed settings
    char tempIndex[] = {-1,8};

    const auto& ports = QSerialPortInfo::availablePorts();
    for(const auto &port : ports){
        this->ports.append(port.portName());
        tempIndex[0]++;
    }
    defaultIndex.append(tempIndex,2);
    currentIndex.append(tempIndex,2);
    settingsName.append("Ports");
    settingsName.append("BaudRate");
    settingsName.append("DataBits");
    settingsName.append("Parity");
    settingsName.append("StopBits");
    settingsName.append("Frequency");
    baudRate.append(QSerialPort::Baud115200);   stringBaudRate.append("115200");
    dataBits.append(QSerialPort::Data8);        stringDataBits.append("8");
    parity.append(QSerialPort::NoParity);       stringParity.append("NoParity");
    stopBits.append(QSerialPort::OneStop);      stringStopBits.append("One");
    frequency.append(0);                        stringFrequency.append("0");
    frequency.append(1);                        stringFrequency.append("1");
    frequency.append(2);                        stringFrequency.append("2");
    frequency.append(3);                        stringFrequency.append("3");
    frequency.append(4);                        stringFrequency.append("4");
    frequency.append(5);                        stringFrequency.append("5");
    frequency.append(6);                        stringFrequency.append("6");
    frequency.append(7);                        stringFrequency.append("7");
    frequency.append(8);                        stringFrequency.append("8");
    frequency.append(9);                        stringFrequency.append("9");
}
QString SerialObject::getName(int itemIndex) const{
    return settingsName[itemIndex];
}
QStringList SerialObject::getCrazySetting(int itemIndex) const{
    switch(itemIndex){
    case 0:
        return ports;
    case 1:
        return stringFrequency;
    default:
        break;
    }
    return QStringList();
}
void SerialObject::sendCrazySetting(int itemIndex,int index){
    currentIndex[itemIndex] = index;
    qDebug() << "---------------------";
    qDebug() << "port name -- " << ports[currentIndex[0]];
    qDebug() << "baud rate -- " << stringBaudRate[0];
    qDebug() << "data bits -- " << stringDataBits[0];
    qDebug() << "parity    -- " << stringParity[0];
    qDebug() << "stop bits -- " << stringStopBits[0];
    qDebug() << "---------------------";
    qDebug() << "frequency -- " << stringFrequency[currentIndex[1]];
    qDebug() << "---------------------" << endl;
}
int SerialObject::getDefaultIndex(int itemIndex) const{
    return defaultIndex[itemIndex];
}
void SerialObject::openSerialPort(){
    serial.setPortName(ports[currentIndex[0]]);
    serial.setBaudRate(baudRate[0]);
    serial.setDataBits(dataBits[0]);
    serial.setParity(parity[0]);
    serial.setStopBits(stopBits[0]);

    if (serial.open(QIODevice::ReadWrite)) {
        qDebug() << "SerialPort Connected...";

    } else {
        qDebug() << "SerialPort connect failed...";
    }
}
void SerialObject::closeSerialPort(){
    if (serial.isOpen()){
        serial.close();
        qDebug() << "SerialPort Disconnected...";
    }
}
void SerialObject::sendStartPacket(){
    qDebug() << "Set Frequency... : " << frequency[currentIndex[1]];
    radioPacket.updateFrequency(frequency[currentIndex[1]]);
    radioPacket.sendStartPacket();
}
