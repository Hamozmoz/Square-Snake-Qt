#ifndef STRUCTS_H
#define STRUCTS_H
#include <qobjectdefs.h>
#include <qtmetamacros.h>
struct Position{
    Q_GADGET
public:
    uint8_t x,y;
    int8_t Displacement;
    Q_PROPERTY(int8_t Displacement READ getDisplacement)
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
    int8_t getDisplacement(){ return Displacement;}
    Position(uint8_t xval = 0, uint8_t yval = 0,int8_t Disval = 0): x(xval),y(yval),Displacement(Disval){}
};
#endif // STRUCTS_H
