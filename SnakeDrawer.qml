import QtQuick
import Snake2
FocusScope {
   property real tilewidth: 0

        id:root
        property real tilesegmentwidth : gamegrid.tilewidth/20

Repeater{
   model:DataContainer.positions
Rectangle{
color: "royalblue"
height: gamegrid.tileheight
width: gamegrid.tilewidth
x: modelData.x * gamegrid.tilewidth
y: modelData.y * gamegrid.tileheight
Behavior on x{
   PropertyAnimation{
      duration: 250
   }
}
Behavior on y{
   PropertyAnimation{
      duration: 250
   }
}
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
            x:DataContainer.positions[0].x* gamegrid.tilewidth + tilesegmentwidth
            y:DataContainer.positions[0].y* gamegrid.tileheight
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