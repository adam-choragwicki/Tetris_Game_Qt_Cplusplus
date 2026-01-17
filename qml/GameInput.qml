// GameInput.qml
import QtQuick

FocusScope {
    focus: true

    Keys.onPressed: (event) => {
        Controller.processKeyPress(event.key, event.isAutoRepeat)
        event.accepted = true
    }

    Keys.onReleased: (event) => {
        Controller.processKeyRelease(event.key, event.isAutoRepeat)
        event.accepted = true
    }
}