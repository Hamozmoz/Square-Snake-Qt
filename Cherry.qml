import QtQuick

FocusScope {
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
    }
}
