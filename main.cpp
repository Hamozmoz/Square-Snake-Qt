#include "GameData.h"
#include "snake.h"
#include <QIcon>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterSingletonInstance("Snake2",1,0,"DataContainer",&(DataContainer::GetData()));
    qmlRegisterSingletonInstance("Snake2",1,0,"Snake",&(Snake::getmover()));
 app.setWindowIcon(QIcon("C:/CppPrograms/Snake2/app_icon.ico"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Snake2", "Main");

    return QGuiApplication::exec();
}
