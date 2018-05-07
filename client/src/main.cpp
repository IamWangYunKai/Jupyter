#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "interaction.h"
void qmlRegister(){
    qmlRegisterType<Interaction>("ZSS", 1, 0, "Interaction");
}
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegister();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
