import QtQuick

Window {
    id: mainWindow
    width: 450
    height: 860
    minimumWidth: 450
    minimumHeight: 860
    visible: true

    Component.onCompleted: {
        if (Controller.startInFullScreenEnabled) {
            console.log("Starting in fullscreen")
            mainWindow.showFullScreen()
        } else {
            console.log("Starting in windowed mode")
            mainWindow.showNormal()
        }
    }

    UiScaler {
        id: uiScaler
        target: gameViewport
        referenceWidth: 450
        referenceHeight: 860
    }

    // Maintain the aspect ratio with black bars
    Rectangle {
        id: letterboxContainer
        anchors.fill: parent
        color: "black"

        // This Item keeps the correct scaling inside any window shape
        Item {
            id: gameViewport
            anchors.centerIn: parent

            readonly property real targetAspect: 450 / 860
            property real currentAspect: letterboxContainer.width / letterboxContainer.height

            // Maintain the aspect ratio and center it
            width: currentAspect > targetAspect ? letterboxContainer.height * targetAspect : letterboxContainer.width
            height: currentAspect > targetAspect ? letterboxContainer.height : letterboxContainer.width / targetAspect

            GameArea {
                id: gameArea
                anchors.fill: parent
                uiScale: uiScaler.scale
            }
        }
    }

    function onChangeGameParameters() {
        gameParametersDialog.open()
        Controller.onChangeGameParametersClicked()
    }

    // Overlays
    EndGameOverlay {
        visible: false
        objectName: "endGameOverlay"
        anchors.fill: parent
        uiScale: uiScaler.scale
        onPlayAgainClicked: Controller.onPlayAgainClicked()

        onChangeGameParametersClicked: {
            onChangeGameParameters()
        }

        onQuitClicked: Controller.onQuitClicked()
    }

    EscapeMenuOverlay {
        visible: false
        objectName: "escapeMenuOverlay"
        anchors.fill: parent
        uiScale: uiScaler.scale
        onResumeClicked: Controller.onResumeClicked()
        onRestartClicked: Controller.onRestartClicked()

        onChangeGameParametersClicked: {
            onChangeGameParameters()
        }

        onQuitClicked: Controller.onQuitClicked()
    }

    GameParametersDialog {
        id: gameParametersDialog
        anchors.centerIn: parent
    }
}
