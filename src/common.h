#pragma once

#include "coordinates.h"
#include <array>
#include <QColor>

using BlockCoordinatesArray = std::array<Coordinates, 4>;

enum class BlockShape
{
    S, Z, I, J, L, O, T
};

const std::vector BLOCK_SHAPES{BlockShape::I, BlockShape::J, BlockShape::L, BlockShape::O, BlockShape::S, BlockShape::T, BlockShape::Z,};

namespace Arena
{
    constexpr int MINIMUM_X = 1;
    constexpr int MINIMUM_Y = 1;
    constexpr int MAXIMUM_X = 10;
    constexpr int MAXIMUM_Y = 20;
    constexpr int BOTTOM_EDGE_Y = MAXIMUM_Y + 1;
}

namespace BlockData
{
    const std::vector<QColor> BLOCK_COLORS = {Qt::cyan, Qt::blue, QColor(255, 165, 0), Qt::yellow, Qt::green, Qt::magenta, Qt::red};
    static constexpr Coordinates STARTING_CENTRAL_SQUARE_COORDINATES{5, 2};
}
