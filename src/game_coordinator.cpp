#include "game_coordinator.h"
#include "block_movement_manager.h"
#include "model/model.h"
#include "active_block_manager.h"
#include "placed_squares.h"
#include "qml_helper.h"
#include "state_machine/i_state_actions.h"

GameCoordinator::GameCoordinator(const GameConfig& gameConfig, Model& model, QmlHelper& qmlHelper, IStateActions& stateActions) : model_(model),
                                                                                                                                  qmlHelper_(qmlHelper),
                                                                                                                                  stateActions_(stateActions),
                                                                                                                                  activeBlockManager_(model_.getActiveBlockManager()),
                                                                                                                                  placedSquares_(model_.getPlacedSquares())
{
    gameLoop_ = std::make_unique<GameLoop>(gameConfig);

    connect(gameLoop_.get(), &GameLoop::tick, this, &GameCoordinator::onGameTick);

    lockTimer_.setSingleShot(true);
    lockTimer_.setInterval(LOCK_DELAY_MS);
    connect(&lockTimer_, &QTimer::timeout, this, &GameCoordinator::onLockTimerTimeout);

    connect(gameLoop_.get(), &GameLoop::gameSpeedLevelChanged, this, &GameCoordinator::gameSpeedLevelChanged);

    stateActions_.setGameState(GameStateType::ReadyToStart);

    // generate a new block as soon as the active block is destroyed
    connect(&activeBlockManager_, &ActiveBlockManager::activeBlockDestroyed, this, &GameCoordinator::createNewBlock);

    createNewBlock();
}

SpeedLevel GameCoordinator::getGameSpeedLevel() const
{
    return gameLoop_->getGameSpeedLevel();
}

void GameCoordinator::startGame()
{
    stateActions_.setGameState(GameStateType::Running);
}

void GameCoordinator::restartGame()
{
    qInfo() << "Restarting game";
    model_.reset();

    stateActions_.setGameState(GameStateType::ReadyToStart);

    startGame();
}

void GameCoordinator::startGameLoop()
{
    gameLoop_->start();
}

void GameCoordinator::stopGameLoop()
{
    gameLoop_->stop();
}

void GameCoordinator::setGameSpeedLevel(const SpeedLevel newSpeedLevel)
{
    gameLoop_->setGameSpeedLevel(newSpeedLevel);
}

void GameCoordinator::softDropBlock()
{
    // Soft drop is just a faster gravity tick. By calling onGameTick manually, the same validation logic is used.
    onGameTick();

    // Game loop timer is restarted to prevent a "double jump" where gravity fires immediately after a manual soft drop.
    gameLoop_->restartTimer();
}

void GameCoordinator::onGameTick()
{
    if (!activeBlockManager_.blockExists())
    {
        return;
    }

    // Try to move down via gravity
    const auto result = BlockMovementManager::simulateMove(activeBlockManager_.getActiveBlock(), Direction::DOWN, placedSquares_);

    if (result.isValid())
    {
        BlockMovementManager::applyResult(activeBlockManager_.getActiveBlock(), result);

        // If we were locking but the block fell (e.g., slid off a ledge), stop locking
        if (isLocking_)
        {
            isLocking_ = false;
            lockTimer_.stop();
        }
    }
    else
    {
        // Block hit the floor/stack
        startLockPhase();
    }
}

void GameCoordinator::onLockTimerTimeout()
{
    // Timer finished, and the block has not moved to a "falling" state
    placeBlock();
    isLocking_ = false;
}

void GameCoordinator::hardDropBlock()
{
    if (!activeBlockManager_.blockExists())
    {
        return;
    }

    const auto result = BlockMovementManager::simulateHardDrop(activeBlockManager_.getActiveBlock(), placedSquares_);

    if (result.isValid())
    {
        BlockMovementManager::applyResult(activeBlockManager_.getActiveBlock(), result);
    }

    // Hard drop bypasses lock delay
    lockTimer_.stop();
    isLocking_ = false;
    placeBlock();
}

void GameCoordinator::moveActiveBlock(const Direction direction)
{
    if (!activeBlockManager_.blockExists())
    {
        return;
    }

    const auto result = BlockMovementManager::simulateMove(activeBlockManager_.getActiveBlock(), direction, placedSquares_);

    if (result.isValid())
    {
        BlockMovementManager::applyResult(activeBlockManager_.getActiveBlock(), result);
        resetLockTimer();
    }
}

void GameCoordinator::startLockPhase()
{
    if (isLocking_)
    {
        return;
    }

    isLocking_ = true;
    lockResetCounter_ = 0;
    lockTimer_.start();
}

void GameCoordinator::resetLockTimer()
{
    // If the player moves/rotates while the block is on the ground, give them more time to make a decision (Infinity rule).
    if (isLocking_ && lockResetCounter_ < MAX_LOCK_RESETS)
    {
        lockTimer_.start();
        lockResetCounter_++;
    }
}

void GameCoordinator::rotateActiveBlock()
{
    if (!activeBlockManager_.blockExists())
    {
        return;
    }

    const auto result = BlockMovementManager::simulateRotation(activeBlockManager_.getActiveBlock(), placedSquares_);

    if (result.isValid())
    {
        BlockMovementManager::applyResult(activeBlockManager_.getActiveBlock(), result);
        resetLockTimer();
    }
}

void GameCoordinator::placeBlock()
{
    if (!activeBlockManager_.blockExists())
    {
        qWarning() << "GameCoordinator::placeBlock: No active block";
        return;
    }

    qDebug() << "Placing block";

    PlacedSquares& placedSquares = placedSquares_;
    const Block& block = activeBlockManager_.getActiveBlock();

    placedSquares.placeBlock(block);

    activeBlockManager_.destroyBlock();

    handleFullRows();
}

void GameCoordinator::handleFullRows()
{
    std::vector<int> fullRows = placedSquares_.findFullRowsNumbers();

    if (fullRows.empty())
    {
        return;
    }

    qInfo() << "Found" << fullRows.size() << "full rows";

    model_.getScoreManager().addRewardForFullRowsToScoreBalance(fullRows.size());

    // Sort rows so we process the shallowest (top-most) row first.
    // This ensures that when we drop rows, we don't mess up the indices of the full rows below them.
    std::ranges::sort(fullRows);

    for (const int rowNumber: fullRows)
    {
        placedSquares_.removeRow(rowNumber, false);
        placedSquares_.dropRowsAboveGivenRow(rowNumber, false);
    }

    model_.updatePlacedSquaresModel();
}

void GameCoordinator::endGame()
{
    qDebug() << "Game over";
    stateActions_.setGameState(GameStateType::Ended);
}

void GameCoordinator::createNewBlock()
{
    qDebug() << "Creating new block";
    activeBlockManager_.createBlock();

    // Check if the new block overlaps with existing squares immediately
    const auto& blockCoordinates = activeBlockManager_.getActiveBlock().getAllSquaresCoordinates();

    if (!BlockMovementManager::validateBlock(blockCoordinates, placedSquares_))
    {
        qInfo() << "Game Over: Block spawned in occupied space.";
        endGame();
    }
}
