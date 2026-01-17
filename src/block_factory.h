#pragma once

#include "block.h"

class BlockFactory
{
public:
    [[nodiscard]] std::unique_ptr<Block> makeBlock(const BlockShape& blockShape, const QColor& color) const;
    [[nodiscard]] std::unique_ptr<Block> makeBlock(const BlockShape& blockShape);
    std::unique_ptr<Block> makeRandomBlock();

private:
    RandomGenerator<QColor> randomColorGenerator{BlockData::BLOCK_COLORS};
    RandomGenerator<BlockShape> randomShapeGenerator{BLOCK_SHAPES};
};
