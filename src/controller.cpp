#include "controller.h"
#include "config/game_config.h"

Controller::Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view)
    : gameConfig_(gameConfig),
      model_(model),
      view_(view),
      gameStateManager_(*this)
{
    qInfo() << "Initializing controller";

    inputHandler_ = std::make_unique<InputHandler>(*this, windowManager_);

    connect(&gameStateManager_, &GameStateManager::gameStateChanged, this, &Controller::gameStateChanged, Qt::UniqueConnection);
}

void Controller::startGameLoop()
{
    qDebug() << "Controller::startGameLoop()";
    gameCoordinator_->startGameLoop();
}

void Controller::stopGameLoop()
{
    qDebug() << "Controller::stopGameLoop()";
    gameCoordinator_->stopGameLoop();
}

void Controller::requestMoveActiveBlock(const Direction direction)
{
    gameCoordinator_->moveActiveBlock(direction);
}

void Controller::requestRotateActiveBlock()
{
    gameCoordinator_->rotateActiveBlock();
}

void Controller::requestSoftDropBlock()
{
    gameCoordinator_->softDropBlock();
}

void Controller::requestHardDropBlock()
{
    gameCoordinator_->hardDropBlock();
}

void Controller::onQmlEngineFullyInitialized()
{
    qDebug() << "QML engine fully initialized";

    windowManager_.setWindow(qmlHelper_.getMainWindow());
    overlayManager_ = std::make_unique<OverlayManager>(qmlHelper_);

    gameCoordinator_ = std::make_unique<GameCoordinator>(gameConfig_, model_, qmlHelper_, *this);

    gameCoordinator_->startGame();
}

void Controller::processKeyPress(const int key, const bool isAutoRepeat)
{
    // qDebug() << "Key pressed:" << key;
    inputHandler_->keyPressed(key, isAutoRepeat);
}

void Controller::processKeyRelease(const int key, const bool isAutoRepeat)
{
    // qDebug() << "Key released:" << key;
    inputHandler_->keyReleased(key, isAutoRepeat);
}

void Controller::onResumeClicked()
{
    qInfo() << "Resume button clicked";
    gameStateManager_.restorePreviousGameState();
}

void Controller::onRestartClicked()
{
    qInfo() << "Restart button clicked";
    gameCoordinator_->restartGame();
}

void Controller::onQuitClicked()
{
    qInfo() << "Quit button clicked";
    emit applicationShutdownRequested();
}

void Controller::onPlayAgainClicked()
{
    qInfo() << "Play again button clicked";
    gameCoordinator_->restartGame();
}

void Controller::onChangeGameParametersClicked()
{
    qDebug() << "Change game parameters button clicked";
}

void Controller::showEscapeMenuOverlay()
{
    overlayManager_->showEscapeMenuOverlay();
}

void Controller::hideEscapeMenuOverlay()
{
    overlayManager_->hideEscapeMenuOverlay();
}

void Controller::showEndGameOverlay()
{
    overlayManager_->showEndGameOverlay(QString::number(model_.getScoreManager().getScore()));
}

void Controller::hideEndGameOverlay()
{
    overlayManager_->hideEndGameOverlay();
}

void Controller::setGameState(const GameStateType newGameState)
{
    gameStateManager_.setGameState(newGameState);
}

void Controller::restorePreviousState()
{
    gameStateManager_.restorePreviousGameState();
}

SpeedLevel Controller::getGameSpeedLevel() const
{
    if (!gameCoordinator_) // QML queries initial game speed before game coordinator gets instantiated
    {
        return gameConfig_.getInitialGameSpeed();
    }

    return gameCoordinator_->getGameSpeedLevel();
}

void Controller::setGameSpeedLevel(const SpeedLevel newSpeedLevel)
{
    qDebug() << "Changing game speed to" << newSpeedLevel;
    gameCoordinator_->setGameSpeedLevel(newSpeedLevel);
    emit gameSpeedLevelChanged(newSpeedLevel);
}
