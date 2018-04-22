#ifndef __INTERACTION_H__
#define __INTERACTION_H__

#include <QObject>
#include "communicator.h"
class Interaction : public QObject
{
    Q_OBJECT
public:
    explicit Interaction(QObject *parent = 0);
    Q_INVOKABLE bool connectSerialPort(bool);
    Q_INVOKABLE bool changeSerialFrequency(int);
    Q_INVOKABLE bool changeSerialPort(int);
    Q_INVOKABLE QStringList getSerialPortsList();
    Q_INVOKABLE int getFrequency();

    Q_INVOKABLE bool send(const QString& str){
        return ZCommunicator::instance()->testSend(str);
    }
    Q_INVOKABLE QStringList getNetworkInterfaces(){
        return ZCommunicator::instance()->updateNetworkInterfaces();
    }
    Q_INVOKABLE bool changeConnection(bool sw){
        if(sw)
            return ZCommunicator::instance()->connect();
        else
            return ZCommunicator::instance()->disconnect();
    }
    Q_INVOKABLE void changeNetworkInterface(int index){
        ZCommunicator::instance()->changeNetworkInterface(index);
    }
    ~Interaction();
public:
signals:
public slots:
};

#endif // __INTERACTION_H__
