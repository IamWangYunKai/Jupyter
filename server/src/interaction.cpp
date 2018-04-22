#include "interaction.h"
#include "zsingleton.h"

namespace {
}
Interaction::Interaction(QObject *parent) : QObject(parent) {
}
Interaction::~Interaction() {
}
bool Interaction::connectSerialPort(bool sw){
    if(sw){
        return ZSS::ZActionModule::instance()->init();
    }
    return ZSS::ZActionModule::instance()->closeSerialPort();
}

bool Interaction::changeSerialFrequency(int frequency){
    return ZSS::ZActionModule::instance()->changeFrequency(frequency);
}

bool Interaction::changeSerialPort(int index){
    return ZSS::ZActionModule::instance()->changePorts(index);
}

QStringList Interaction::getSerialPortsList(){
    return ZSS::ZActionModule::instance()->updatePortsList();
}
int Interaction::getFrequency(){
    return ZSS::ZActionModule::instance()->getFrequency();
}
