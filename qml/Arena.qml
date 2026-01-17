// Arena.qml
import QtQuick

Item {
    id: arenaRoot

    width: (columnsCount * tileSize) + offset        // left offset + columns * tileSize
    height: (rowsCount * tileSize) + (offset * 2)    // top offset + rows * tileSize + bottom offset

    required property real uiScale // scale propagated from UiScaler
    required property real tileSize
    required property real offset

    // BASE constants
    readonly property int columnsCount: 10
    readonly property int rowsCount: 20
    readonly property int baseWallThickness: 5

    readonly property real wallThickness: baseWallThickness * uiScale

    // checkerboard colors
    readonly property color backgroundTileColor1: Qt.rgba(170 / 255, 215 / 255, 81 / 255, 1)
    readonly property color backgroundTileColor2: Qt.rgba(162 / 255, 209 / 255, 73 / 255, 1)
    readonly property color wallColor: "white"

    readonly property bool drawBackground: false

    /* BACKGROUND TILES (checkerboard) */
    Repeater {
        model: drawBackground ? columnsCount * rowsCount : 0
        delegate: Rectangle {
            width: tileSize
            height: tileSize
            property int gridX: index % columnsCount
            property int gridY: Math.floor(index / columnsCount)

            x: offset + gridX * tileSize
            y: offset + gridY * tileSize

            color: ((gridX % 2 === 0)
                ? (gridY % 2 === 0 ? backgroundTileColor1 : backgroundTileColor2)
                : (gridY % 2 === 0 ? backgroundTileColor2 : backgroundTileColor1))
        }
    }

    /* Arena walls - rendered as thin rectangles around the playfield */
    // Left wall
    Rectangle {
        x: 0
        y: 0
        width: wallThickness
        height: arenaRoot.height
        color: wallColor
    }

    // Right wall
    Rectangle {
        x: arenaRoot.width
        y: 0
        width: wallThickness
        height: arenaRoot.height
        color: wallColor
    }

    // Top wall
    Rectangle {
        x: 0
        y: 0
        width: arenaRoot.width
        height: wallThickness
        color: wallColor
    }

    // Bottom wall
    Rectangle {
        x: 0
        y: arenaRoot.height - wallThickness
        width: arenaRoot.width
        height: wallThickness
        color: wallColor
    }
}
