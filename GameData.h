#ifndef GAMEDATA_H
#define GAMEDATA_H
#include <deque>
#include <random>
#include <QtQml>
#include <qtmetamacros.h>
#include <QVariant>
#include <vector>
#include<QObject>
#include <QChronoTimer>
#include "positionsmodel.h"
  enum TileState :uint8_t{ snake, Free };

class DataContainer: public QObject{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QList<Direction> directions READ Getdirections NOTIFY directionschanged)
    Q_PROPERTY(QAbstractListModel* Positions READ Getpositions CONSTANT)
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
    PositionsModel* Getpositions();
    std::deque<Position> &GetPositions();
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
 PositionsModel Positions;
std::vector<Position> FreeTiles;
    void SpawnCherry();
std::vector<TileState> TilesStates;
    int8_t Rows{15},Columns{17};
};

#endif // GAMEDATA_H
