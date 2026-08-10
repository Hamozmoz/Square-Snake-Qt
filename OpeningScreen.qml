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
}
