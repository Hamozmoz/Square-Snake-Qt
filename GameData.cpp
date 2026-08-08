#include <snakemover.h>
#include<GameData.h>




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
        for(auto i : Positions){
            list.append(i);
        }
        return list;
    }
    DataContainer::DataContainer()
    {
        timer = new QChronoTimer(std::chrono::milliseconds(250),this);
        connect(this,&DataContainer::gamestarted,this,&DataContainer::StartGame);
        connect(timer,&QChronoTimer::timeout,&Snakemover::getmover(),&Snakemover::snakemovement);
    }
    void DataContainer::StartGame()
    {
        timer->start();
        SpawnCherry();
    }
    // Getters For Values
    std::vector<Position>& DataContainer::GetPositions(){
        return Positions;
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
    // Normal Functions
    void DataContainer::SpawnCherry(){
        uint8_t row{230};
        uint8_t col{230};
        do{
            row = Rowdistributer(cherrygen);
            col = Coldistributer(cherrygen);
        }while(IsSnakePart(col,row));
        Cherrypos = Position(col,row);
        ThereisCherry = true;
        emit cherryStateChanged();
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


