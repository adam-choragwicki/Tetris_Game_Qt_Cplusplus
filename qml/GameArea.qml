// GameArea.qml
import QtQuick

Item {
    id: gameArea

    required property real uiScale // scale propagated from UiScaler

    // BASE constants
    readonly property int baseSquareSize: 30
    readonly property int baseOffset: 5

    // Scaled values used to compute geometry
    property real tileSize: baseSquareSize * uiScale
    property real offset: baseOffset * uiScale

    Arena {
        anchors.centerIn: parent
        id: arena
        uiScale: gameArea.uiScale

        tileSize: gameArea.tileSize
        offset: gameArea.offset

        // Active block
        Repeater {
            model: (ActiveBlock && ActiveBlock.squares) ? ActiveBlock.squares : []
            delegate: Square {
                width: tileSize
                height: tileSize
                x: offset + (modelData.x - 1) * tileSize
                y: offset + (modelData.y - 1) * tileSize
                color: ActiveBlock.color
            }
        }

        // Placed squares
        Repeater {
            model: PlacedSquaresModel
            delegate: Square {
                width: tileSize
                height: tileSize
                x: offset + (model.x - 1) * tileSize
                y: offset + (model.y - 1) * tileSize
                color: model.color
            }
        }
    }

    Column {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "SCORE: " + ScoreManager.score
            color: "white"
            font.pixelSize: 40 * uiScale
            font.bold: true
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "SPEED LEVEL: " + Controller.gameSpeedLevel
            color: "white"
            font.pixelSize: 40 * uiScale
            font.bold: true
        }
    }


    GameInput {
        anchors.fill: parent
    }
}
