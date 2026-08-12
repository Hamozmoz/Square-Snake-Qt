#include <snake.h>
#include<GameData.h>

DataContainer::DataContainer()
{
    timer = new QChronoTimer(std::chrono::milliseconds(125),this);

    connect(this,&DataContainer::gamestarted,this,&DataContainer::startGame);
    connect(timer,&QChronoTimer::timeout,&Snake::getmover(),&Snake::snakemovement);
}

// Directions Reader
    QList<DataContainer::Direction> DataContainer::Getdirections(){
        QList<Direction> list ;
            for(auto i : Directions){
                list.append(i);
        }
            return list;
    }
// Positions Reader
    QList<Position> DataContainer::Getpositions(){
        QList<Position> list;
        for(auto i : Positions.positions){
            list.append(i);
        }
        return list;
    }

    // Free Tiles List Reader
    QList<Position> DataContainer::GetFreeTiles(){
        QList<Position> list;
        for(auto Pos : FreeTiles){
            list.append(Pos);
        }
        return list;
    }

    // Getters For Values
    std::deque<Position>& DataContainer::GetPositions(){
        return Positions.positions;
    }
    std::vector<DataContainer::Direction>& DataContainer::GetDirections(){
        return Directions;
    }
    const bool DataContainer::GetCherryState(){
      return  ThereisCherry ;
    }
    const uint8_t DataContainer::GetRows(){
        return Rows;
    }
    const uint8_t DataContainer::GetColumns(){
        return Columns;
    }
    const Position DataContainer::GetCherry(){
        return Cherrypos;
    }
    const bool DataContainer::GetGameState(){

        return GameOver;

    }
   const bool DataContainer::GetGameOn(){

        return GameOn;
    }
   void DataContainer::WriteGameOn(const bool gameon){
        emit GameStateChanged();
       GameOn = gameon;
   }
   void DataContainer::WriteGameState(const bool gameover){
        emit GameStateChanged();
       GameOver = gameover;
   }
    // Normal Functions

    void DataContainer::startGame()
    {

GameOn = true;
        timer->start();
        initFreeTiles();
        SpawnCherry();

    }
    void DataContainer::SpawnCherry(){

        for(uint8_t Col {0};Col< Columns ;Col++){
            for(uint8_t row {0};row<Rows; row++ ){
                if( TilesStates[getMatrixIndex(Col,row)] == TileState::Free){
                    FreeTiles.push_back(Position{Col,row});
                }
            }
        }
        std::uniform_int_distribution<uint8_t> distributer{0,static_cast<uint8_t>(FreeTiles.size() -1)};
        uint8_t index= distributer(cherrygen);
        Cherrypos = FreeTiles[index];
        ThereisCherry = true;
        emit cherryStateChanged();

        FreeTiles.clear();
    }
    bool DataContainer::IsSnakePart(uint8_t x,uint8_t y){
        for(auto pos: DataContainer::GetData().GetPositions()){
            if(pos.x ==x|| pos.y == y)
            {
                return true;
            }
        }
        return false;
    }
    void DataContainer::initFreeTiles(){
        TilesStates.assign(Columns * Rows ,TileState::Free);

        for(auto Pos : Positions.positions){
            TilesStates[getMatrixIndex(Pos.x,Pos.y)] = TileState::snake;
            }



        }
    void DataContainer::resetToMenu() {
        GameOn = false;
        GameOver = false;
        Directions.assign({Up,Up,Up});
        Positions.positions.assign({{9,7},{9,8},{9,9}});

        emit GameStateChanged();
        emit positionschanged();
        emit directionschanged();
    }


