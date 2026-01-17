set(MODULE_NAME TetrisQml)
set(LIB_NAME ${MODULE_NAME}Lib) # TetrisQmlLib

qt_add_library(${LIB_NAME} STATIC)

target_link_libraries(${LIB_NAME} PRIVATE Qt6::Quick)

qt_add_qml_module(${LIB_NAME}
        URI ${MODULE_NAME}
        VERSION 1.0
        OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/TetrisQml
        QML_FILES
        Main.qml
        GameArea.qml
        Arena.qml
        GameInput.qml
        UiScaler.qml
        GameParametersDialog.qml
        Square.qml

        overlays/EndGameOverlay.qml
        overlays/EscapeMenuOverlay.qml
)
