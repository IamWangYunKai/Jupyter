#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QUdpSocket>
#include "singleton.hpp"

class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(QObject *parent = nullptr);
    QStringList& updateNetworkInterfaces();
    void changeNetworkInterface(int);
    void changeRobotID(int index);
    bool connect();
    bool disconnect();
    // test TODO;
    bool testSend(const QString&);
    void pos(int, int);
    void dir(int, int);
    void plan_pos();
    void plan_dir();
private slots:
    void testReceive();
    void sendCommand();
private:
    bool isConnect = false;
    QUdpSocket sendSocket,receiveSocket;
    QStringList networkInterfaceNames;
    QStringList networkInterfaceReadableNames;
    int networkInterfaceIndex;
    int robotID = 0;
    float vx = 0;//实际值
    float _vx = 0;//理论值
    float vy = 0;//实际值
    float _vy = 0;//理论值
    float vr = 0;//实际值
    float _vr = 0;//理论值
};
typedef Singleton<Communicator> ZCommunicator;
#endif // COMMUNICATOR_H
