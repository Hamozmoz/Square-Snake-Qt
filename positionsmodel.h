#ifndef POSITIONSMODEL_H
#define POSITIONSMODEL_H
#include "Structs.h"
#include <QObject>
#include <QtQmlIntegration>
#include <deque>
#include <iostream>
class PositionsModel : public QAbstractListModel
{
    enum Positionroles{
        x = Qt::UserRole + 1,
        y,
        Displacement
    };

    Q_OBJECT
    QML_UNCREATABLE("You Can't Create A Positions Model In Qml")
    int rowCount(const QModelIndex& parent = QModelIndex()) const override{
        return positions.size();
    }
    QVariant data(const QModelIndex& index, int role) const override{
        if(index.row() < 0 || index.row() >= positions.size()){
            std::cout <<" \033[31mInvalid Index ! The Size Of The Model Is" << positions.size() << "And You Wrote :" << index.row() << "\033[0m\n";
            return QVariant();
        }
        if(role == Positionroles::x){ return positions[index.row()].x;}
        if (role == Positionroles::y){ return positions[index.row()].y;}
        if(role == Positionroles::Displacement){return positions[index.row()].Displacement;}
        return QVariant();
    }
    QHash<int,QByteArray> roleNames() const override{
        QHash<int,QByteArray> roles;
        roles[Positionroles::x] = "x";
        roles[Positionroles::y] = "y";
        roles[Positionroles::Displacement] = "Displacement";
        return roles;

    }

public:
  Q_INVOKABLE  uint8_t getx(int index){
        return positions[index].x;
    }
  Q_INVOKABLE  uint8_t gety(int index){
        return positions[index].y;
    }
  Q_INVOKABLE  int8_t getDisplacement(int index){
      return positions[index].Displacement;
  }
    //Functions For Changing The Model's Data
    void BeginInsertRows(int first , int last ){
        QModelIndex Parent = QModelIndex();
        beginInsertRows(Parent,first,last);
    }
    void BeginInsertRows(int first  ){
        QModelIndex Parent = QModelIndex();
        beginInsertRows(Parent,first,first);
    }
    void EndInsertRows(){
        endInsertRows();
    }
    void DataChanged(  int first,int last)
    {
        QModelIndex Firstindex= createIndex(first,0);
        QModelIndex Lastindex= createIndex(last,0);
        dataChanged(Firstindex,Lastindex);
    }
    void DataChanged(  int first)
    {
        QModelIndex Firstindex= createIndex(first,0);

        dataChanged(Firstindex,Firstindex);
    }
    std::deque<Position> positions{ {9,7},{9,8},{9,9} };
    PositionsModel();
};

#endif // POSITIONSMODEL_H
