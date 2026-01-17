// Square.qml
import QtQuick

Item {
    id: root

    property alias color: baseColorRect.color
    property real radius: Math.min(width, height) * 0.18
    property real bevelThickness: Math.min(width, height) * 0.12

    // Derived colors
    property color midColor: baseColorRect.color
    property color lightColor: Qt.lighter(midColor, 1.25)
    property color darkColor: Qt.darker(midColor, 1.25)

    // ===== Visuals =====
    Item {
        id: visual
        anchors.fill: parent

        // --- Base tile with vertical gradient ---
        Rectangle {
            id: baseColorRect
            anchors.fill: parent
            radius: root.radius

            gradient: Gradient {
                GradientStop { position: 0.0; color: root.lightColor }
                GradientStop { position: 0.5; color: root.midColor }
                GradientStop { position: 1.0; color: root.darkColor }
            }

            border.color: Qt.darker(root.midColor, 1.35)
            border.width: Math.max(1, Math.round(Math.min(width, height) * 0.04))
        }

        // --- Upper-left bevel highlight ---
        Rectangle {
            width: parent.width - root.bevelThickness
            height: parent.height - root.bevelThickness
            x: 0
            y: 0
            radius: root.radius

            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(1, 1, 1, 0.18) }
                GradientStop { position: 1.0; color: Qt.rgba(1, 1, 1, 0.0) }
            }
        }

        // --- Lower-right inner shadow (depth) ---
        Rectangle {
            anchors.fill: parent
            radius: root.radius

            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(0, 0, 0, 0.0) }
                GradientStop { position: 0.6; color: Qt.rgba(0, 0, 0, 0.06) }
                GradientStop { position: 1.0; color: Qt.rgba(0, 0, 0, 0.18) }
            }
        }

        // --- Glossy cap highlight ---
        Rectangle {
            width: Math.max(2, Math.round(parent.width * 0.45))
            height: Math.max(2, Math.round(parent.height * 0.20))
            x: Math.round(parent.width * 0.12)
            y: Math.round(parent.height * 0.06)
            radius: height / 2

            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(1, 1, 1, 0.9) }
                GradientStop { position: 1.0; color: Qt.rgba(1, 1, 1, 0.05) }
            }
        }
    }

    // --- Outer stroke (tile separation) ---
    Rectangle {
        anchors.fill: parent
        radius: root.radius
        color: "transparent"
        border.color: Qt.darker(root.midColor, 1.6)
        border.width: Math.max(1, Math.round(Math.min(width, height) * 0.03))
    }
}
