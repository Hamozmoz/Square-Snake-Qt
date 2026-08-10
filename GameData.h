#ifndef GAMEDATA_H
#define GAMEDATA_H
#include <random>
#include <QtQml>
#include <qtmetamacros.h>
#include <QVariant>
#include <vector>
#include<QObject>
#include <QChronoTimer>
  enum TileState :uint8_t{ snake, Free };
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
    bool operator==( Position other)
    {
        return(this->x == other.x && this->y == other.y);
    }
    Position operator-(const Position pos2 ){
        Position newposition;
        newposition.x = this->x - pos2.x;
        newposition.y = this->y - pos2.y;
        return newposition;
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
    Q_PROPERTY(QList<Position> freeTiles READ GetFreeTiles NOTIFY FreeTilesChanged)
    Q_PROPERTY(bool GameOver READ GetGameState WRITE WriteGameState NOTIFY GameStateChanged)
    Q_PROPERTY(bool GameOn READ GetGameOn WRITE WriteGameOn NOTIFY GameStateChanged)
public:
    Position Cherrypos;
    bool GameOver{false};
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
   const bool GetGameState();
   QList<Position> GetFreeTiles();
   const bool GetGameOn();
   void WriteGameOn(const bool gameon);
   void WriteGameState(const bool gameover);
  Q_INVOKABLE void resetToMenu();
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
    // Tiles Changed
    void FreeTilesChanged();
    // GameState Changed
    void GameStateChanged();

private:
    bool IsSnakePart(uint8_t x, uint8_t y);


    std::random_device rd;
    std::mt19937 cherrygen{ rd()};

    DataContainer();



 void initFreeTiles();


 public:
 Q_INVOKABLE void startGame();
 bool GameOn{false};
 QChronoTimer* timer;
  std::vector<Direction> Directions{Up,Up,Up};
 std::vector<Position> Positions{ {9,7},{9,8},{9,9} };
std::vector<Position> FreeTiles;
    void SpawnCherry();
std::vector<TileState> TilesStates;
    uint8_t Rows{15},Columns{17};
};

#endif // GAMEDATA_H
