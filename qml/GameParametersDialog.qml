// GameParametersDialog.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: dialog
    modal: true
    width: 400
    height: 250
    title: ""

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        // ===== Title === ==
        Label {
            text: "Game parameters"
            font.pixelSize: 22
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        // ===== Form =====
        GridLayout {
            columns: 2
            rowSpacing: 12
            columnSpacing: 16
            Layout.fillWidth: true

            Label {
                text: "Speed:"
                font.bold: true
            }
            ComboBox {
                id: speedComboBox
                model: GameConfig.gameSpeedOptions
                Layout.fillWidth: true

                Component.onCompleted: {
                    const idx = model.indexOf(Controller.gameSpeedLevel)

                    if (idx === -1) {
                        console.error("Current game speed not found in gameSpeedOptions_:", Controller.gameSpeedLevel)
                    } else {
                        currentIndex = idx
                    }
                }
            }
        }

        Item {
            Layout.fillHeight: true
        } // spacer

        // ===== Buttons =====
        RowLayout {
            Layout.fillWidth: true
            spacing: 16
            Layout.alignment: Qt.AlignHCenter

            Button {
                text: "Cancel"
                Layout.preferredWidth: 120
                onClicked: dialog.close()
            }

            Button {
                text: "OK"
                Layout.preferredWidth: 120
                onClicked: {
                    Controller.setGameSpeedLevel(speedComboBox.currentValue)
                    dialog.close()
                }
            }
        }
    }
}
