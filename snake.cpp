#include "snake.h"
DataContainer::Direction* Headdirection = &(DataContainer::GetData().Directions.front());


Position* HeadPosition = &(DataContainer::GetData().Positions.front());
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
        for(size_t i {0} ; i< DataContainer::GetData().Directions.size();i++){
            if(DataContainer::GetData().Directions[i] == DataContainer::Direction::Up){

                if(DataContainer::GetData().Positions[i].y -1 < 0){
                    DataContainer::GetData().Positions[i].y = DataContainer::GetData().GetRows();

                }
                DataContainer::GetData().Positions[i].y --;

            }
            else if (DataContainer::GetData().Directions[i] == DataContainer::Direction::Down){
                if(DataContainer::GetData().Positions[i].y +1 ==DataContainer::GetData().GetRows())
                {
                    DataContainer::GetData().Positions[i].y= -1;
                }
              DataContainer::GetData().Positions[i].y ++;
            }
            else if(DataContainer::GetData().Directions[i] == DataContainer::Direction::Left){
                if(DataContainer::GetData().Positions[i].x -1 < 0){
                    DataContainer::GetData().Positions[i].x = DataContainer::GetData().GetColumns();
                }
                DataContainer::GetData().Positions[i].x --;
            }else if (DataContainer::GetData().Directions[i] == DataContainer::Direction::Right){
                if(DataContainer::GetData().Positions[i].x + 1 == DataContainer::GetData().GetColumns()){
                    DataContainer::GetData().Positions[i].x = -1;
                }
                DataContainer::GetData().Positions[i].x ++;
            }else{
                return;
            }

            UpdateTileStates();
            emit DataContainer::GetData().positionschanged();
        }
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
        CalculateEyeAngle();}
    }
    void Snake::EatCherry(){
        if (DataContainer::GetData().Positions[0].x == DataContainer::GetData().Cherrypos.x && DataContainer::GetData().Positions[0].y == DataContainer::GetData().Cherrypos.y){
            DataContainer::GetData().ThereisCherry = false;
            emit DataContainer::GetData().cherryStateChanged();
            GrowSnake();
            DataContainer::GetData().SpawnCherry();
        }

    }
    void Snake::GrowSnake(){
        DataContainer::GetData().Directions.push_back(DataContainer::GetData().Directions.back());
        if(DataContainer::GetData().Directions.back() == DataContainer::Up){
            DataContainer::GetData().Positions.push_back(Position(DataContainer::GetData().Positions.back().x,(DataContainer::GetData().Positions.back().y + 1)));
        }else if(DataContainer::GetData().Directions.back() == DataContainer::Down){
            DataContainer::GetData().Positions.push_back(Position(DataContainer::GetData().Positions.back().x, DataContainer::GetData().Positions.back().y -1));
        }else if(DataContainer::GetData().Directions.back() == DataContainer::Right){
            DataContainer::GetData().Positions.push_back(Position(DataContainer::GetData().Positions.back().x -1 ,DataContainer::GetData().Positions.back().y));
        }else if (DataContainer::GetData().Directions.back() == DataContainer::Left){
            DataContainer::GetData().Positions.push_back(Position(DataContainer::GetData().Positions.back().x + 1, DataContainer::GetData().Positions.back().y));
        }
        HeadPosition = &(DataContainer::GetData().Positions.front());
        Headdirection = &(DataContainer::GetData().Directions.front());
        DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions.back().x,DataContainer::GetData().Positions.back().y)] = TileState::snake;

    }
    void Snake::UpdateTileStates(){
        DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions[0].x,DataContainer::GetData().Positions[0].y)] = TileState::snake;
        if(DataContainer::GetData().Directions.back() == DataContainer::Up){
            DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions.back().x,DataContainer::GetData().Positions.back().y + 1)] = TileState::Free;
        }else if(DataContainer::GetData().Directions.back() == DataContainer::Down){
             DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions.back().x,DataContainer::GetData().Positions.back().y - 1)] = TileState::Free;
        }else if(DataContainer::GetData().Directions.back() == DataContainer::Right){
             DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions.back().x-1,DataContainer::GetData().Positions.back().y )] = TileState::Free;
        }else if(DataContainer::GetData().Directions.back() == DataContainer::Left){
            DataContainer::GetData().TilesStates[getMatrixIndex(DataContainer::GetData().Positions.back().x+1,DataContainer::GetData().Positions.back().y )] = TileState::Free;
    }

    }
    bool Snake::GameOver(){
        for(size_t i {DataContainer::GetData().Positions.size() - 1};i > 0 ; i--){
            if(DataContainer::GetData().Positions[i] == DataContainer::GetData().Positions[0]){
        DataContainer::GetData().GameOver = true;
                emit DataContainer::GetData().GameStateChanged();
        DataContainer::GetData().timer->stop();
                return true;
            }
        }

                emit DataContainer::GetData().GameStateChanged();
        return false;
    }
    void Snake::CalculateEyeAngle()
    {
        double Dx =  HeadPosition->x -DataContainer::GetData().Cherrypos.x ;
        double Dy =   HeadPosition->y - DataContainer::GetData().Cherrypos.y;
        AngleOfSnakeEye = (std::atan2(Dy,Dx)) *(180.0/pi);
        emit AngleOfSnakeEyeChanged();
    }