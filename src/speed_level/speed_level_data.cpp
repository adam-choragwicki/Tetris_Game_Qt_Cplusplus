#include "speed_level_data.h"

using namespace std::chrono_literals;

constexpr std::array<SpeedLevelData, 20> SPEED_LEVELS{
    {
        {LEVEL1, 1000ms},
        {LEVEL2, 950ms},
        {LEVEL3, 900ms},
        {LEVEL4, 850ms},
        {LEVEL5, 800ms},
        {LEVEL6, 750ms},
        {LEVEL7, 700ms},
        {LEVEL8, 650ms},
        {LEVEL9, 600ms},
        {LEVEL10, 550ms},
        {LEVEL11, 500ms},
        {LEVEL12, 450ms},
        {LEVEL13, 400ms},
        {LEVEL14, 350ms},
        {LEVEL15, 300ms},
        {LEVEL16, 250ms},
        {LEVEL17, 200ms},
        {LEVEL18, 150ms},
        {LEVEL19, 100ms},
        {LEVEL20, 50ms},
    }
};
