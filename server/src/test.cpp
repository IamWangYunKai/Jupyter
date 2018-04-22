#include "test.h"
#include "proto/zss_cmd.pb.h"
#include "zsingleton.h"
#include <QTest>
#include <QElapsedTimer>
Test::Test(QObject *parent) : QObject(parent)
{

}
void Test::testAM(){
    QElapsedTimer timer;
    timer.start();
    ZSS::Protocol::Robots_Command commands;
    auto command = commands.add_command();
    command->set_robot_id(1);
    for(int i=0;i<1000;i++){
        command->set_velocity_x(0.2);
        ZSS::ZActionModule::instance()->sendLegacy(commands);
        QTest::qWait(16);
    }
}
