#pragma once

#include <QVariantList>
#include <array>
#include "speed_level/speed_level.h"
#include "speed_level/speed_level_data.h"

class GameConfig : public QObject
{
    Q_OBJECT

public:
    explicit GameConfig(QObject* parent = nullptr) : QObject(parent)
    {}

    Q_PROPERTY(QVariantList gameSpeedOptions READ getGameSpeedOptions CONSTANT)

    QVariantList getGameSpeedOptions() const
    {
        QVariantList list;

        for (const SpeedLevelData& speedLevelData: SPEED_LEVELS)
        {
            list.append(QVariant::fromValue(speedLevelData.level));
        }

        return list;
    }

    constexpr SpeedLevel getInitialGameSpeed() const
    {
        return initialGameSpeedLevel_;
    }

    static constexpr SpeedLevel initialGameSpeedLevel_{LEVEL1};
};
