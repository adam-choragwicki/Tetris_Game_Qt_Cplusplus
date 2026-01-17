#pragma once

#include <chrono>
#include <array>
#include "speed_level.h"

struct SpeedLevelData
{
    SpeedLevel level;
    std::chrono::milliseconds tickInterval;
};

extern const std::array<SpeedLevelData, 20> SPEED_LEVELS;
