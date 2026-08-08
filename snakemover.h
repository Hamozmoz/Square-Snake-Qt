#ifndef SNAKEMOVER_H
#define SNAKEMOVER_H
#include <deque>
#include <QObject>
#include <QtQml>
#include <GameData.h>
class Snakemover : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    static Snakemover& getmover();
    Q_INVOKABLE void takeInput( DataContainer::Direction direction = DataContainer::Null);
    void snakemovement();

signals:

private:
    std::deque<char> Movements;
    void RotateHead();
    Snakemover() = default;
    void movesegments();
    void rotatesnake();
};

#endif // SNAKEMOVER_H
