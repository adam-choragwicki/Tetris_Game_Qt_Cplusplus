#pragma once

#include "block_base.h"

class JBlock : public BlockBase
{
public:
    explicit JBlock();
    void RotateBlock(const PlacedSquares& placedBlocks) override;

private:
    int m_CurrentRotation;
};
