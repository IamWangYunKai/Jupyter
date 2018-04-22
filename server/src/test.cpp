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
    auto command2 = commands.add_command();
    auto command3 = commands.add_command();
    auto command4 = commands.add_command();
    command->set_robot_id(2);
    command2->set_robot_id(4);
    command3->set_robot_id(1);
    command4->set_robot_id(4);
    for(int i=0;i<100;i++){
        ZSS::ZActionModule::instance()->sendLegacy(commands);
        QTest::qWait(16);
    }
}
