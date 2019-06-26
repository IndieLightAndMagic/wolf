import QtQuick 2.13
import QtQuick.Controls 2.5
import SceneGraphRendering 1.0
import QtQuick.Dialogs 1.1

SceneRender {
        id: renderer

        opacity: 0
        Component.onCompleted: {

            renderer.opacity = 1;
            console.log("Finished the renderer loading.")
            
        }
        Keys.onPressed : console.log("Keys on pressed")
    }
