import QtQuick

FocusScope {
property alias timer : timer

   Rectangle{
       focus: true
       Keys.onSpacePressed:{
DataContainer.resetToMenu()
       }z:1
       width: window.width
       height: window.height/4
       color: "royalblue"
       opacity: 0.6
y:window.height /2 - height/2

Text{
    opacity: 1
    height: parent.height
    font.pixelSize: height /2
    text: "You Lost !"
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
    Text{
        id : startagaintext
        text: "Press Space To Start Again !"
        font.pixelSize: parent.font.pixelSize /2
y: parent.height /2 + font.pixelSize /2
Timer{
    id: timer
    interval: 600
    running: true
    repeat: true
    onTriggered: startagaintext.visible = !startagaintext.visible
}
    }
  }
   }





}
