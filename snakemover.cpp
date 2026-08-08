#include "snakemover.h"

        DataContainer::Direction& Headdirection = DataContainer::GetData().GetDirections()[0];

    Snakemover& Snakemover::getmover()
    {
       static Snakemover mover;
        return mover;
    }
    void Snakemover::movesegments()
    {
        std::vector<DataContainer::Direction>& Directions = DataContainer::GetData().GetDirections();
        std::vector<Position>& Positions = DataContainer::GetData().GetPositions();
        for(size_t i {0} ; i< Directions.size();i++){
            if(Directions[i] == DataContainer::Direction::Up){
                if(Positions[i].y -1 < 0){
                    Positions[i].y = DataContainer::GetData().GetRows();

                }
                Positions[i].y --;
            }
            else if (Directions[i] == DataContainer::Direction::Down){
                if(Positions[i].y +1 ==DataContainer::GetData().GetRows())
                {
                    Positions[i].y= -1;
                }
              Positions[i].y ++;
            }
            else if(Directions[i] == DataContainer::Direction::Left){
                if(Positions[i].x -1 < 0){
                    Positions[i].x = DataContainer::GetData().GetColumns();
                }
                Positions[i].x --;
            }else if (Directions[i] == DataContainer::Direction::Right){
                if(Positions[i].x + 1 == DataContainer::GetData().GetColumns()){
                    Positions[i].x = -1;
                }
                Positions[i].x ++;
            }else{
                return;
            }
            emit DataContainer::GetData().positionschanged();
        }
    }
    void Snakemover::takeInput( DataContainer::Direction direction )
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
    void Snakemover::rotatesnake(){
        for(size_t i = {DataContainer::GetData().GetDirections().size() -1};i> 0;i--)
        {
            DataContainer::GetData().GetDirections()[i] = DataContainer::GetData().GetDirections()[i-1];
        }
    }
    void Snakemover::RotateHead(){
        if(Movements[0] == 'w' && Headdirection != DataContainer::Down){
            Headdirection = DataContainer::Up;
        }else if (Movements[0] == 's' && Headdirection != DataContainer::Up){
            Headdirection = DataContainer::Down;
        }else if (Movements[0]== 'a' && Headdirection != DataContainer::Right){
            Headdirection = DataContainer::Left;
        }else if (Movements[0]== 'd'&& Headdirection != DataContainer::Left){
            Headdirection = DataContainer::Right;
        }
        if(!Movements.empty()){
            Movements.pop_front();
        }
    }
    void Snakemover::snakemovement(){
        RotateHead();
        movesegments();
        rotatesnake();
    }