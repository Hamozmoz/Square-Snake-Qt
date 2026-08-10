import QtQuick

FocusScope
{
    focus: true
    Rectangle{
        focus: true

        id: screen
        color: "royalblue"
        height: window.height
        width : window.width
        property real screenWidthPart :  width/30
        property real screenHeightPart :  height/20
        Text{
            x: screen.screenWidthPart *9
            y: screen.screenHeightPart * 4
            font.pixelSize: screen.screenWidthPart *3
 font.family: "Consolas"
            text:  "Square\n     Snake"
        }
        Text{
            id : openingtext
             x: screen.screenWidthPart *6
             y: screen.screenHeightPart * 15
             font.family: "Segoe UI"
        font.pixelSize: screen.screenWidthPart * 1.5
        text:  "Press Space To Continue !"
        Timer {
            interval: 560
            repeat: true
            running: true
            onTriggered: openingtext.visible = !openingtext.visible
        }
        }
    }
    Rectangle{
        id: eyewhite
        color: "white"
    width: screen.screenWidthPart * 8
    height: width
y: screen.screenWidthPart
    radius : width/2
    Rectangle{
        id: eyeblack
    anchors.verticalCenter: eyewhite.verticalCenter

        color: "black"
        transform: Rotation{
id : openingscreenblackeye
            origin.x :eyeblack.width
            origin.y : eyeblack.height/2
        }
        width: parent.width/2
       height: width
       radius: width/2
    }

    }
MouseArea{
anchors.fill: screen
hoverEnabled: true
onPositionChanged: openingscreenblackeye.angle =Snake.calculateOpeningScreenEyeAngle(mouseX,mouseY,eyewhite.x + eyewhite.width/2,eyewhite.y + eyewhite.height/2)
}}




