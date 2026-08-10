#ifndef SNAKE_H
#define SNAKE_H
#include <deque>
#include <QObject>
#include <QtQml>
#include <GameData.h>
int getMatrixIndex(int Col,int Row);
class Snake : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(double SnakeEyeAngle READ GetAngleOfSnakeEye NOTIFY AngleOfSnakeEyeChanged)
public:
    static Snake& getmover();
 Q_INVOKABLE   double calculateEyeAngle(const double& mousex,const double& mousey,const double& eyex, const double& eyey );
    Q_INVOKABLE void takeInput( DataContainer::Direction direction = DataContainer::Null);
    void snakemovement();
    void UpdateTileStates();
    bool GameOver();
    double GetAngleOfSnakeEye();
signals:
    void AngleOfSnakeEyeChanged();
private:
    double AngleOfSnakeEye{0};
    std::deque<char> Movements;
    void RotateHead();
    Snake() = default;
    void movesegments();
    void rotatesnake();
    void EatCherry();
    void GrowSnake();


};

#endif // SNAKE_H
