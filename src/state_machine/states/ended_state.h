#pragma once

#include "state_machine/abstract_state.h"

class EndedState : public AbstractState
{
public:
    EndedState(IStateActions& stateActions) : AbstractState("Ended", GameStateType::Ended, stateActions)
    {}

    void entered() override
    {
        qDebug() << "Entered state: Ended";
        stateActions_.showEndGameOverlay();
    }

    void exited() override
    {
        qDebug() << "Exited state: Ended";
        stateActions_.hideEndGameOverlay();
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::ReadyToStart:
                break;

            default:
                handleIllegalTransition(newState);
        }

        printTransition(newState);
    }
};
