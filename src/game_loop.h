#pragma once

#include <QTimer>
#include <chrono>
#include "speed_level/speed_level.h"

class GameConfig;

class GameLoop : public QObject
{
    Q_OBJECT

signals:
    void gameSpeedLevelChanged(SpeedLevel level);
    void tick();

public:
    explicit GameLoop(const GameConfig& gameConfig);
    void start();
    void stop();

    SpeedLevel getGameSpeedLevel() const { return gameSpeedLevel_; }
    void setGameSpeedLevel(SpeedLevel newGameSpeedLevel);

    void restartTimer();

private slots:
    void execute();

private:
    QTimer timer_;

    SpeedLevel gameSpeedLevel_;

    inline static int tickCounter_{};
};
