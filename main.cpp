#include "GameData.h"
#include "snake.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterSingletonInstance("Snake2",1,0,"DataContainer",&(DataContainer::GetData()));
    qmlRegisterSingletonInstance("Snake2",1,0,"Snake",&(Snake::getmover()));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Snake2", "Main");

    return QGuiApplication::exec();
}
