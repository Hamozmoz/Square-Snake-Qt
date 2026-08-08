import QtQuick
import Snake2
Item {

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
}
