#include "game_loop.h"
#include "config/game_config.h"
#include "speed_level/speed_level_utils.h"

GameLoop::GameLoop(const GameConfig& gameConfig) : timer_(this)
{
    timer_.setTimerType(Qt::PreciseTimer);

    setGameSpeedLevel(gameConfig.getInitialGameSpeed());

    connect(&timer_, &QTimer::timeout, this, &GameLoop::execute);
}

void GameLoop::start()
{
    timer_.start();
}

void GameLoop::stop()
{
    timer_.stop();
}

void GameLoop::setGameSpeedLevel(const SpeedLevel newGameSpeedLevel)
{
    if (gameSpeedLevel_ == newGameSpeedLevel)
    {
        qWarning() << "GameLoop::setGameSpeedLevel: Speed level already set to " << newGameSpeedLevel;
        return;
    }

    // qDebug() << "GameLoop::setGameSpeedLevel: " << newGameSpeedLevel;

    gameSpeedLevel_ = newGameSpeedLevel;

    const SpeedLevelData& speedLevelData = retrieveSpeedLevelData(newGameSpeedLevel);
    timer_.setInterval(speedLevelData.tickInterval);

    emit gameSpeedLevelChanged(newGameSpeedLevel);
}

void GameLoop::restartTimer()
{
    // qDebug() << "GameLoop::restartTimer()";
    timer_.start();
}

void GameLoop::execute()
{
    qDebug() << "GameLoop: Tick" << ++tickCounter_;
    emit tick();
}
