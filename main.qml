import QtQuick 2.5
import QtQuick.Window 2.3

Window {
    id: mainWindow
    visible: true

    signal qmlSignal(var anObject)

    Item {
        focus: true
        opacity: 0

        Keys.onPressed: {
            //console.log("onReleased ", event.key)
            mainWindow.qmlSignal(event.key)
        }

    }
}
