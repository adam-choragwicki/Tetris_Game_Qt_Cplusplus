import QtQuick

Item {
    property bool scalingEnabled: true

    required property Item target // The root item whose size is used for scaling.

    // Reference resolution for UI layout.
    required property int referenceWidth
    required property int referenceHeight

    // Scaling factors. UI scale should be based mostly on height for consistency.
    property real scale: scalingEnabled ? (target.height / referenceHeight) : 1.0
}
