#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "zsingleton.h"
#include "interaction.h"
#include "translator.hpp"
#include "paraminterface.h"
#include "test.h"
void qmlRegister(){
    qmlRegisterType<Translator>("ZSS", 1, 0, "Translator");
    qmlRegisterType<Interaction>("ZSS", 1, 0, "Interaction");
    qmlRegisterType<Test>("ZSS", 1, 0, "Test");
    qmlRegisterType<ParamInterface>("ZSS", 1, 0, "ParamModel");
}

int main(int argc, char *argv[]){
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegister();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/src/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
