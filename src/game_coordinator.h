#pragma once

#include "game_loop.h"
#include "direction.h"

class GameConfig;
class ActiveBlockManager;
class PlacedSquares;
class QmlHelper;
class IStateActions;
class Model;

class GameCoordinator : public QObject
{
    Q_OBJECT

signals:
    void gameSpeedLevelChanged(SpeedLevel);

public:
    explicit GameCoordinator(const GameConfig& gameConfig, Model& model, QmlHelper& qmlHelper, IStateActions& stateActions);

    SpeedLevel getGameSpeedLevel() const;

    void startGame();
    void restartGame();

    void startGameLoop();
    void stopGameLoop();

    void setGameSpeedLevel(SpeedLevel newSpeedLevel);

    void softDropBlock();
    void hardDropBlock();

    void moveActiveBlock(Direction direction);
    void rotateActiveBlock();

    void placeBlock();

    void handleFullRows();

    void startLockPhase();
    void resetLockTimer();

private slots:
    void endGame();
    void createNewBlock();

    void onGameTick(); // triggered by GameLoop (Gravity)
    void onLockTimerTimeout(); // triggered when the block finally locks

private:
    Model& model_;
    QmlHelper& qmlHelper_;
    IStateActions& stateActions_;

    ActiveBlockManager& activeBlockManager_;
    PlacedSquares& placedSquares_;

    std::unique_ptr<GameLoop> gameLoop_;

    QTimer lockTimer_;
    bool isLocking_ = false;
    int lockResetCounter_ = 0;
    const int MAX_LOCK_RESETS = 15;
    const int LOCK_DELAY_MS = 500;
};
