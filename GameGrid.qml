import QtQuick

Item {
    id: gridroot
property int rows : 15
property int columns: 17
property real tilewidth: window.width/columns
property real tileheight :window.height/rows
Repeater{
    model: rows *columns
    Loader{
     sourceComponent:    Rectangle{
            x:currentcolumn *gridroot.tilewidth
            y:currentrow *gridroot.tileheight
            width: gridroot.tilewidth
            height : gridroot.tileheight
            property int currentrow : Math.floor(index/gridroot.columns)
            property int currentcolumn :  index % gridroot.columns
       color: (currentcolumn + currentrow)%2 == 0?"#A2D149":"#AAD751"
        }

}


}


}
