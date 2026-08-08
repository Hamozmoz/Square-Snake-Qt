#ifndef GAMEDATA_H
#define GAMEDATA_H
#include <random>
#include <QtQml>
#include <qtmetamacros.h>
#include <QVariant>
#include <vector>
#include<QObject>
#include <QChronoTimer>

struct Position{
    Q_GADGET
public:
    uint8_t x,y;
    Q_PROPERTY(uint8_t x READ getx WRITE setx )
    Q_PROPERTY(uint8_t y READ gety WRITE sety )
    // x functions
    uint8_t getx(){return x;}
    void setx(uint8_t xvalue)
    {
        if(x != xvalue)
        {
        x = xvalue;
        }
    }
    //y functions

    uint8_t gety(){return y; }

    void sety(uint8_t yvalue)
    {if(y != yvalue )
        {
            y = yvalue;
        }
    }

    Position(uint8_t xval = 0, uint8_t yval = 0): x(xval),y(yval){}
};
class DataContainer: public QObject{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QList<Direction> directions READ Getdirections NOTIFY directionschanged)
    Q_PROPERTY(QList<Position> positions READ Getpositions NOTIFY positionschanged)
    Q_PROPERTY(bool ThereisACherry READ GetCherryState NOTIFY cherryStateChanged)
    Q_PROPERTY(uint8_t Rows READ GetRows NOTIFY RowsChanged)
    Q_PROPERTY(uint8_t Columns READ GetColumns NOTIFY ColumnsChanged)
    Q_PROPERTY(Position CherryPosition READ GetCherry NOTIFY cherryStateChanged)
public:
    Position Cherrypos;
    bool ThereisCherry {false};
enum Direction: uint8_t{ Up, Down, Right, Left ,Null};
    // Singelton Instance Getter
  static  DataContainer& GetData()
    {
        static DataContainer container;
        return container;
    }
    Q_ENUM( Direction);
    QList<Direction> Getdirections();
    QList<Position> Getpositions();
    std::vector<Position>& GetPositions();
    std::vector<Direction>& GetDirections();
   const bool GetCherryState();
    const uint8_t GetRows();
   const uint8_t GetColumns();
    const Position GetCherry();
signals:
    // Directions Signal
    void directionschanged();
    // Positions Signal
    void positionschanged();
    // Game Started Signal
    void gamestarted();
    // Cherry Signals
    void cherryStateChanged();
    // Rows And Columns Signals
    void RowsChanged();
    void ColumnsChanged();
private:
    uint8_t Rows{15},Columns{17};
    bool IsSnakePart(uint8_t x, uint8_t y);
    std::uniform_int_distribution<uint8_t> Coldistributer{0,17};
    std::uniform_int_distribution<uint8_t> Rowdistributer{0,15};
    std::random_device rd;
    std::mt19937 cherrygen{ rd()};
    void SpawnCherry();
    QChronoTimer* timer;
    DataContainer();
    void StartGame();
 std::vector<Direction> Directions{Left,Up,Up};
    std::vector<Position> Positions{ {10,7},{10,8},{10,9} };
};

#endif // GAMEDATA_H
