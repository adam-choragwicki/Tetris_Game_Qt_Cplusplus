#pragma once

#include <QDebug>

enum class GameStateType
{
    Initialization, // App just started, creating an arena etc.
    ReadyToStart, // Everything ready, waiting for the player's input to start.
    Running, // Game loop active.
    EscapeMenu, // Escape menu overlay is displayed.
    Ended, // Game stopped because there is no place to generate new active block.
};

inline QDebug operator<<(QDebug debug, const GameStateType state)
{
    QDebugStateSaver saver(debug);
    debug.nospace();

    switch (state)
    {
        case GameStateType::Initialization: return debug << "Initialization";
        case GameStateType::ReadyToStart: return debug << "ReadyToStart";
        case GameStateType::Running: return debug << "Running";
        case GameStateType::EscapeMenu: return debug << "EscapeMenu";
        case GameStateType::Ended: return debug << "Ended";

        default:
            qFatal() << "Unknown game state";
    }
}
