import QtQuick 2.9
import QtQuick.Window 2.3
import QtMultimedia 5.9

Window {
    id: mainWindow
    //visible: true

    signal qmlSignal(var anObject)

    Item {
        focus: true
        anchors.fill: parent
        //opacity: 0

        MediaPlayer {
            id: mediaplayer
            objectName: "mp"
            autoPlay: true
        }

        VideoOutput {
            id: videoOutput
            source: mediaplayer
            visible: mediaplayer.hasVideo
            anchors {
                fill: parent
            }
        }

        Keys.onPressed: {
            //console.log("onReleased ", event.key)
            mainWindow.qmlSignal(event.key)
        }

    }
}
