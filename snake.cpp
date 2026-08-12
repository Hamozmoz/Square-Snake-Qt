#include "snake.h"
#include <QDebug>
DataContainer::Direction* Headdirection = &(DataContainer::GetData().Directions.front());


Position* HeadPosition = &(DataContainer::GetData().Positions.positions.front());
constexpr double pi = 3.14159265358979323846;
int getMatrixIndex(int Col, int Row)
{



    if((Row * DataContainer::GetData().Columns + Col) < DataContainer::GetData().TilesStates.size()){
        return Row * DataContainer::GetData().Columns + Col;}
    for(int i{0}; i< DataContainer::GetData().TilesStates.size();i++){
        if(DataContainer::GetData().TilesStates[i] == TileState::Free){
            return i;
        }
    }
    return 0;
}

double Snake::GetAngleOfSnakeEye(){
    return AngleOfSnakeEye;
}
    Snake& Snake::getmover()
    {
       static Snake mover;
        return mover;
    }
    void Snake::movesegments()
    {
/*
        static int counts {0};

            static QElapsedTimer myTimer;

        qDebug() << counts<<" Time passed since Last Move :" << myTimer.elapsed()  << "ms";
       myTimer.restart();
        counts ++;
*/
       if(DataContainer::GetData().Directions[0] == DataContainer::Up){
            if(DataContainer::GetData().Positions.positions[0].y -1 < 0)
           {
               DataContainer::GetData().Positions.positions.push_front({DataContainer::GetData().Positions.positions[0].x,static_cast<uint8_t>(DataContainer::GetData().Rows -1)});
            }else
            {
            DataContainer::GetData().Positions.positions.push_front({DataContainer::GetData().Positions.positions[0].x,static_cast<uint8_t>(DataContainer::GetData().Positions.positions[0].y -1)});
            }
       }else if(DataContainer::GetData().Directions[0] == DataContainer::Down){
           if(DataContainer::GetData().Positions.positions[0].y + 1 >= DataContainer::GetData().Rows){
               DataContainer::GetData().Positions.positions.push_front({DataContainer::GetData().Positions.positions[0].x , 0});
           }else{
         DataContainer::GetData().Positions.positions.push_front({DataContainer::GetData().Positions.positions[0].x,static_cast<uint8_t>(DataContainer::GetData().Positions.positions[0].y +1)});
           }}else if(DataContainer::GetData().Directions[0] == DataContainer::Right){
           if(DataContainer::GetData().Positions.positions[0].x +1 >= DataContainer::GetData().Columns){
               DataContainer::GetData().Positions.positions.push_front({0,DataContainer::GetData().Positions.positions[0].y });
           }else{
           DataContainer::GetData().Positions.positions.push_front({static_cast<uint8_t>(DataContainer::GetData().Positions.positions[0].x +1),DataContainer::GetData().Positions.positions[0].y });
           } }else if(DataContainer::GetData().Directions[0] == DataContainer::Left){
           if(DataContainer::GetData().Positions.positions[0].x -1 <0 ){
               DataContainer::GetData().Positions.positions.push_front({static_cast<uint8_t>(DataContainer::GetData().Columns-1),DataContainer::GetData().Positions.positions[0].y });
           }else{  DataContainer::GetData().Positions.positions.push_front({static_cast<uint8_t>(DataContainer::GetData().Positions.positions[0].x -1),DataContainer::GetData().Positions.positions[0].y });
           }}
       DataContainer::GetData().Positions.positions.pop_back();
            UpdateTileStates();
        HeadPosition = &(DataContainer::GetData().Positions.positions.front());
            emit DataContainer::GetData().positionschanged();

        }

    void Snake::takeInput( DataContainer::Direction direction )
    {
        if(Movements.size() >= 2){
            return;
        }

        if( direction == DataContainer::Down){
            Movements.push_back('s') ;
        }else if( direction == DataContainer::Up){
            Movements.push_back('w');
        }else if( direction == DataContainer::Left){
            Movements.push_back('a');
        }else if ( direction == DataContainer::Right){
            Movements.push_back('d');
        }


    }
    void Snake::rotatesnake(){
        for(size_t i = {DataContainer::GetData().Directions.size() -1};i> 0;i--)
        {
            DataContainer::GetData().Directions[i] = DataContainer::GetData().Directions[i-1];
        }
    }
    void Snake::RotateHead(){

        if(Movements[0] == 'w' && *Headdirection != DataContainer::Down){
            *Headdirection = DataContainer::Up;
        }else if (Movements[0] == 's' && *Headdirection != DataContainer::Up){
            *Headdirection = DataContainer::Down;
        }else if (Movements[0]== 'a' && *Headdirection != DataContainer::Right){
            *Headdirection = DataContainer::Left;
        }else if (Movements[0]== 'd'&& *Headdirection != DataContainer::Left){
            *Headdirection = DataContainer::Right;
        }

        if(!Movements.empty()){
            emit DataContainer::GetData().directionschanged();
            Movements.pop_front();
        }
    }
    void Snake::snakemovement(){
        if(!GameOver()){
        RotateHead();
        movesegments();
        EatCherry();
        rotatesnake();
        calculateEyeAngle(DataContainer::GetData().Cherrypos.x,DataContainer::GetData().Cherrypos.y,HeadPosition->x,HeadPosition->y);
        }
    }
    void Snake::EatCherry(){
        if (DataContainer::GetData().Positions.positions[0].x == DataContainer::GetData().Cherrypos.x && DataContainer::GetData().Positions.positions[0].y == DataContainer::GetData().Cherrypos.y){
            DataContainer::GetData().ThereisCherry = false;
            emit DataContainer::GetData().cherryStateChanged();
            GrowSnake();
            DataContainer::GetData().SpawnCherry();
        }

    }
    void Snake::GrowSnake(){
        DataContainer::GetData().Directions.push_back(DataContainer::GetData().Directions.back());
        if(DataContainer::GetData().Directions.back() == DataContainer::Up){
            DataContainer::GetData().Positions.positions.push_back(Position(DataContainer::GetData().Positions.positions.back().x,(DataContainer::GetData().Positions.positions.back().y + 1)));
        }else if(DataContainer::GetData().Directions.back() == DataContainer::Down){
            DataContainer::GetData().Positions.positions.push_back(Position(DataContainer::GetData().Positions.positions.back().x, DataContainer::GetData().Positions.positions.back().y -1));
        }else if(DataContainer::GetData().Directions.back() == DataContainer::Right){
            DataContainer::GetData().Positions.positions.push_back(Position(DataContainer::GetData().Positions.positions.back().x -1 ,DataContainer::GetData().Positions.positions.back().y));
        }else if (DataContainer::GetData().Directions.back() == DataContainer::Left){
            DataContainer::GetData().Positions.positions.push_back(Position(DataContainer::GetData().Positions.positions.back().x + 1, DataContainer::GetData().Positions.positions.back().y));
        }

        Headdirection = &(DataContainer::GetData().Directions.front());
        DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions.positions.back().x,DataContainer::GetData().Positions.positions.back().y)] = TileState::snake;

    }
    void Snake::UpdateTileStates(){
        DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions.positions[0].x,DataContainer::GetData().Positions.positions[0].y)] = TileState::snake;
        if(DataContainer::GetData().Directions.back() == DataContainer::Up){
            DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions.positions.back().x,DataContainer::GetData().Positions.positions.back().y + 1)] = TileState::Free;
        }else if(DataContainer::GetData().Directions.back() == DataContainer::Down){
             DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions.positions.back().x,DataContainer::GetData().Positions.positions.back().y - 1)] = TileState::Free;
        }else if(DataContainer::GetData().Directions.back() == DataContainer::Right){
             DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions.positions.back().x-1,DataContainer::GetData().Positions.positions.back().y )] = TileState::Free;
        }else if(DataContainer::GetData().Directions.back() == DataContainer::Left){
            DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions.positions.back().x+1,DataContainer::GetData().Positions.positions.back().y )] = TileState::Free;
    }

    }
    bool Snake::GameOver(){
        for(size_t i {DataContainer::GetData().Positions.positions.size() - 1};i > 0 ; i--){
            if(DataContainer::GetData().Positions.positions[i] == DataContainer::GetData().Positions.positions[0]){
        DataContainer::GetData().GameOver = true;
                emit DataContainer::GetData().GameStateChanged();
        DataContainer::GetData().timer->stop();
                return true;
            }
        }

                emit DataContainer::GetData().GameStateChanged();
        return false;
    }

      //  double Dx =  HeadPosition->x -DataContainer::GetData().Cherrypos.x ;
     //   double Dy =   HeadPosition->y - DataContainer::GetData().Cherrypos.y;



    double Snake::calculateEyeAngle(const double& mousex,const double& mousey,const double& eyex, const double& eyey )
    {
        double Dx =    eyex- mousex;
        double Dy =     eyey- mousey;
        AngleOfSnakeEye =(std::atan2(Dy,Dx)) *(180.0/pi);
        emit AngleOfSnakeEyeChanged();

        return AngleOfSnakeEye;

    }