#pragma once

#include "input_handler.h"
#include "window_manager.h"
#include "model/model.h"
#include "state_machine/game_state_manager.h"
#include "overlay_manager.h"
#include "qml_helper.h"
#include "game_coordinator.h"
#include <QQmlApplicationEngine>

class Controller : public QObject, public IStateActions
{
    Q_OBJECT

signals:
    void applicationShutdownRequested();
    void gameStateChanged();
    void gameSpeedLevelChanged(SpeedLevel gameSpeedLevel);

public slots:
    void onQmlEngineFullyInitialized();
    void processKeyPress(int key, bool isAutoRepeat);
    void processKeyRelease(int key, bool isAutoRepeat);
    void onResumeClicked();
    void onRestartClicked();
    void onQuitClicked();
    void onPlayAgainClicked();
    void onChangeGameParametersClicked();

    void setGameSpeedLevel(SpeedLevel newSpeedLevel);

public:
    Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view);

    // IStateActions implementation
    void startGameLoop() override;
    void stopGameLoop() override;
    void requestMoveActiveBlock(Direction direction) override;
    void requestRotateActiveBlock() override;
    void requestSoftDropBlock() override;
    void requestHardDropBlock() override;

    void showEscapeMenuOverlay() override;
    void hideEscapeMenuOverlay() override;
    void showEndGameOverlay() override;
    void hideEndGameOverlay() override;

    void setGameState(GameStateType newGameState) override;
    void restorePreviousState() override;

    [[nodiscard]] GameStateManager& getStateManager() { return gameStateManager_; }

    [[nodiscard]] bool isStartInFullScreenEnabled() const { return windowManager_.isStartInFullScreenEnabled(); }
    Q_PROPERTY(bool startInFullScreenEnabled READ isStartInFullScreenEnabled CONSTANT)

    Q_PROPERTY(SpeedLevel gameSpeedLevel READ getGameSpeedLevel NOTIFY gameSpeedLevelChanged)
    SpeedLevel getGameSpeedLevel() const;

private:
    const GameConfig& gameConfig_;
    Model& model_;
    QQmlApplicationEngine& view_;

    QmlHelper qmlHelper_{view_};
    GameStateManager gameStateManager_;
    WindowManager windowManager_;
    std::unique_ptr<OverlayManager> overlayManager_;
    std::unique_ptr<InputHandler> inputHandler_;
    std::unique_ptr<GameCoordinator> gameCoordinator_;
};
