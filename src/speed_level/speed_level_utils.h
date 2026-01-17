#pragma once

#include "speed_level_data.h"
#include <stdexcept>

inline const SpeedLevelData& retrieveSpeedLevelData(const SpeedLevel level)
{
    for (const auto& data: SPEED_LEVELS)
    {
        if (data.level == level)
        {
            return data;
        }
    }

    throw std::logic_error("Invalid SpeedLevel value");
}
