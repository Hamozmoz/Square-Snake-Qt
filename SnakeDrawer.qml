import QtQuick
import Snake2
FocusScope {
   property real tilewidth: 0

        id:root
        property real tilesegmentwidth : gamegrid.tilewidth/20

Repeater{
   model:DataContainer.Positions
id:snakeReapeater

Rectangle{
color: "royalblue"
height: gamegrid.tileheight
width: gamegrid.tilewidth
property real displacement : model.Displacement
x: (DataContainer.directions[index] === DataContainer.Left || DataContainer.directions[index] === DataContainer.Right)?
model.x * gamegrid.tilewidth+ model.Displacement * gamegrid.horizontalMoveDistance : model.x * gamegrid.tilewidth
y: (DataContainer.directions[index] === DataContainer.Down || DataContainer.directions[index] === DataContainer.Up)?
    model.y * gamegrid.tileheight + model.Displacement * gamegrid.verticalMoveDistance:
    model.y * gamegrid.tileheight

}



}

Item{
        Row{
           id:row
           transform: Rotation{
              id: rowrotation
           origin.x: gamegrid.tilewidth /2
           origin.y: gamegrid.tileheight/2
angle:DataContainer.directions[0] ===DataContainer.Up? 0:
DataContainer.directions[0] === DataContainer.Right?90:
DataContainer.directions[0] === DataContainer.Down ? 180:
270
           }

           Connections{
           target : DataContainer.Positions
              function onDataChanged(topLeft, bottomRight){
           row.x =   (DataContainer.directions[0] === DataContainer.Left || DataContainer.directions[0] === DataContainer.Right)?
                      DataContainer.Positions.getx(0) * gamegrid.tilewidth  + tilesegmentwidth + DataContainer.Positions.getDisplacement(0) *gamegrid.horizontalMoveDistance:
                      DataContainer.Positions.getx(0) * gamegrid.tilewidth
                 row.y = (DataContainer.directions[0] === DataContainer.Down || DataContainer.directions[0] === DataContainer.Up)?
                         DataContainer.Positions.gety(0) * gamegrid.tileheight + DataContainer.Positions.getDisplacement(0) * gamegrid.verticalMoveDistance
               :         DataContainer.Positions.gety(0) * gamegrid.tileheight

           }

}


            spacing: root.tilesegmentwidth * 2
        Repeater{
            model : 2
            Rectangle{
                id: eyewhite
                color: "white"
            width: root.tilesegmentwidth * 8
            height: width

            radius : width/2
            Rectangle{
                id: eyeblack
            anchors.verticalCenter: eyewhite.verticalCenter

                color: "black"
                transform: Rotation{
  angle: Snake.SnakeEyeAngle - rowrotation.angle
                    origin.x :eyeblack.width
                    origin.y : eyeblack.height/2
                }
                width: parent.width/2
               height: width
               radius: width/2
            }
        }}

    }
}
}