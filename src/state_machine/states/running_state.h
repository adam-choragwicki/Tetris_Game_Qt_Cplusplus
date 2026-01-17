#pragma once

#include "state_machine/abstract_state.h"

class RunningState : public AbstractState
{
public:
    explicit RunningState(IStateActions& stateActions) : AbstractState("RunningState", GameStateType::Running, stateActions)
    {}

    void entered() override
    {
        qDebug() << "Entered state: Running";
        stateActions_.startGameLoop();
    }

    void exited() override
    {
        qDebug() << "Exited state: Running";
        stateActions_.stopGameLoop();
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::EscapeMenu:
            case GameStateType::Ended:
                break;

            default:
                handleIllegalTransition(newState);
        }

        printTransition(newState);
    }

    void onKeyPress(const int key) override
    {
        switch (key)
        {
            case Qt::Key_Left:
            case Qt::Key_A:
                stateActions_.requestMoveActiveBlock(Direction::LEFT);
                break;

            case Qt::Key_Right:
            case Qt::Key_D:
                stateActions_.requestMoveActiveBlock(Direction::RIGHT);
                break;

            case Qt::Key_Up:
            case Qt::Key_W:
                stateActions_.requestRotateActiveBlock();
                break;

            case Qt::Key_Down:
            case Qt::Key_S:
                stateActions_.requestSoftDropBlock();
                break;

            case Qt::Key_Space:
                stateActions_.requestHardDropBlock();
                break;

            case Qt::Key_Escape:
                stateActions_.setGameState(GameStateType::EscapeMenu);
                break;

            default:
                break;
        }
    }
};
