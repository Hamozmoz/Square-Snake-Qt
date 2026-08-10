import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import Snake2
Window{
    id: window
visible: true
width: 1000
height : 1000
Loader{
    active: !DataContainer.GameOn && !DataContainer.GameOver
    focus: !DataContainer.GameOn && !DataContainer.GameOver
    sourceComponent:
    OpeningScreen{
        Keys.onSpacePressed: if(!DataContainer.GameOn) {DataContainer.startGame()}
focus: true
    }
}


Loader{
    id:gridloader
focus : DataContainer.GameOn && !DataContainer.GameOver
active: DataContainer.GameOn? true : false
sourceComponent:
GameGrid{
id: gamegrid
focus : true

Keys.onPressed: (event)=>{
                event.accepted = true
                    if(event.key === Qt.Key_W  || event.key === Qt.Key_Up){
                    Snake.takeInput(DataContainer.Up)
                    }else if(event.key === Qt.Key_D|| event.key === Qt.Key_Right){
                        Snake.takeInput(DataContainer.Right)
                    }else if(event.key === Qt.Key_S || event.key === Qt.Key_Down){
                        Snake.takeInput(DataContainer.Down)
                    }else if (event.key === Qt.Key_A|| event.key === Qt.Key_Left){
                        Snake.takeInput(DataContainer.Left)
                    }else{
                        event.accepted = false;
                    }

                }
SnakeDrawer{

}

Loader{
active: (DataContainer.ThereisACherry&& DataContainer.GameOn && gridloader.progress >= 1)? true:false
sourceComponent:
    Cherry{

}
}



}





}
Loader {
    focus: DataContainer.GameOver&&DataContainer.GameOn

    id : gameoverscreenloader
    active: DataContainer.GameOver&&DataContainer.GameOn
    sourceComponent: GameoverScreen{
          focus: true

    }

}
}