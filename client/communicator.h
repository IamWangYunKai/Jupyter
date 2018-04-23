#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QUdpSocket>
#include <singleton.hpp>

class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(QObject *parent = nullptr);
    QStringList& updateNetworkInterfaces();
    void changeNetworkInterface(int);
    bool connect();
    bool disconnect();
    // test TODO;
    bool testSend(const QString&);
    void pos(int, int);
    void dir(int, int);
private slots:
    void testReceive();
    QByteArray sendCommand();
private:
    QUdpSocket sendSocket,receiveSocket;
    QStringList networkInterfaceNames;
    QStringList networkInterfaceReadableNames;
    int networkInterfaceIndex;
    float vx = 0;
    float last_vx = 0;
    float vy = 0;
    float last_vy = 0;
    float vr = 0;
    float last_vr = 0;
};
typedef Singleton<Communicator> ZCommunicator;
#endif // COMMUNICATOR_H
