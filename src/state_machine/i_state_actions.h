#pragma once

#include "game_state_type.h"
#include "direction.h"

class IStateActions
{
public:
    virtual ~IStateActions() = default;

    // Game loop control
    virtual void startGameLoop() = 0;
    virtual void stopGameLoop() = 0;

    virtual void requestMoveActiveBlock(Direction nextDirection) = 0;
    virtual void requestRotateActiveBlock() = 0;
    virtual void requestSoftDropBlock() = 0;
    virtual void requestHardDropBlock() = 0;

    // Overlays
    virtual void showEscapeMenuOverlay() = 0;
    virtual void hideEscapeMenuOverlay() = 0;
    virtual void showEndGameOverlay() = 0;
    virtual void hideEndGameOverlay() = 0;

    // State transitions
    virtual void setGameState(GameStateType newType) = 0;
    virtual void restorePreviousState() = 0;
};
