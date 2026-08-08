import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import Snake2
Window{
    id: window
visible: true
width: 1000
height : 1000
GameGrid{
id: gamegrid
focus : true
   Keys.onSpacePressed: {
        DataContainer.gamestarted()}
Keys.onPressed: (event)=>{
                event.accepted = true
                    if(event.key === Qt.Key_W ){
                    Snakemover.takeInput(DataContainer.Up)
                    }else if(event.key === Qt.Key_D){
                        Snakemover.takeInput(DataContainer.Right)
                    }else if(event.key === Qt.Key_S){
                        Snakemover.takeInput(DataContainer.Down)
                    }else if (event.key === Qt.Key_A){
                        Snakemover.takeInput(DataContainer.Left)
                    }else{
                        event.accepted = false;
                    }

                }
}
SnakeDrawer{

}
Loader{
active: DataContainer.ThereisACherry? true:false
sourceComponent:
Image{
    id: cherry
    width: gamegrid.tilewidth
    height: gamegrid.tileheight
x: DataContainer.CherryPosition.x * gamegrid.tilewidth
y: DataContainer.CherryPosition.y * gamegrid.tileheight
    source:"file:///C:/Users/hamoz/Downloads/Browser Games - Google Snake Game - Playable Characters & Objects - Food.png"
SequentialAnimation{
    running: true
    loops: Animation.Infinite
    PropertyAnimation
    {
        target: cherry
        property: "scale"
        from: 1
        to: 1.3
        duration: 300
    }
    PropertyAnimation
    {
        target: cherry
        property: "scale"
        from: 1.3
        to: 1
        duration: 300
    }

}
}}



}

