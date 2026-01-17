#include "common_test_fixture.h"
#include "block_factory.h"
#include "block_movement_manager.h"

class BlockRotationTest : public CommonTestFixture
{
protected:
    BlockFactory blockFactory_;
    PlacedSquares placedSquares_;
    SimulationResult blockRotationSimulationResult_;
};

TEST_F(BlockRotationTest, RotateIBlock)
{
    auto iBlock = blockFactory_.makeBlock(BlockShape::I, DEFAULT_SQUARE_COLOR);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*iBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*iBlock, blockRotationSimulationResult_);

    EXPECT_EQ(iBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(iBlock->getSquareCoordinates(1), Coordinates({5, 1}));
    EXPECT_EQ(iBlock->getSquareCoordinates(2), Coordinates({5, 3}));
    EXPECT_EQ(iBlock->getSquareCoordinates(3), Coordinates({5, 4}));

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*iBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*iBlock, blockRotationSimulationResult_);

    EXPECT_EQ(iBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(iBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(iBlock->getSquareCoordinates(2), Coordinates({6, 2}));
    EXPECT_EQ(iBlock->getSquareCoordinates(3), Coordinates({7, 2}));
}

TEST_F(BlockRotationTest, RotateJBlock)
{
    auto jBlock = blockFactory_.makeBlock(BlockShape::J, DEFAULT_SQUARE_COLOR);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*jBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*jBlock, blockRotationSimulationResult_);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*jBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*jBlock, blockRotationSimulationResult_);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*jBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*jBlock, blockRotationSimulationResult_);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*jBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*jBlock, blockRotationSimulationResult_);

    EXPECT_EQ(jBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(2), Coordinates({6, 2}));
    EXPECT_EQ(jBlock->getSquareCoordinates(3), Coordinates({6, 3}));
}

TEST_F(BlockRotationTest, RotateLBlock)
{
    auto lBlock = blockFactory_.makeBlock(BlockShape::L, DEFAULT_SQUARE_COLOR);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*lBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*lBlock, blockRotationSimulationResult_);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*lBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*lBlock, blockRotationSimulationResult_);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*lBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*lBlock, blockRotationSimulationResult_);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*lBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*lBlock, blockRotationSimulationResult_);

    EXPECT_EQ(lBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(lBlock->getSquareCoordinates(1), Coordinates({6, 2}));
    EXPECT_EQ(lBlock->getSquareCoordinates(2), Coordinates({4, 2}));
    EXPECT_EQ(lBlock->getSquareCoordinates(3), Coordinates({4, 3}));
}

TEST_F(BlockRotationTest, RotateOBlock)
{
    auto oBlock = blockFactory_.makeBlock(BlockShape::O, DEFAULT_SQUARE_COLOR);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*oBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*oBlock, blockRotationSimulationResult_);

    EXPECT_EQ(oBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(oBlock->getSquareCoordinates(1), Coordinates({6, 2}));
    EXPECT_EQ(oBlock->getSquareCoordinates(2), Coordinates({5, 1}));
    EXPECT_EQ(oBlock->getSquareCoordinates(3), Coordinates({6, 1}));

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*oBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*oBlock, blockRotationSimulationResult_);

    EXPECT_EQ(oBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(oBlock->getSquareCoordinates(1), Coordinates({6, 2}));
    EXPECT_EQ(oBlock->getSquareCoordinates(2), Coordinates({5, 1}));
    EXPECT_EQ(oBlock->getSquareCoordinates(3), Coordinates({6, 1}));
}

TEST_F(BlockRotationTest, RotateSBlock)
{
    auto sBlock = blockFactory_.makeBlock(BlockShape::S, DEFAULT_SQUARE_COLOR);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*sBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*sBlock, blockRotationSimulationResult_);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*sBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*sBlock, blockRotationSimulationResult_);

    EXPECT_EQ(sBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(sBlock->getSquareCoordinates(1), Coordinates({4, 3}));
    EXPECT_EQ(sBlock->getSquareCoordinates(2), Coordinates({5, 3}));
    EXPECT_EQ(sBlock->getSquareCoordinates(3), Coordinates({6, 2}));
}

TEST_F(BlockRotationTest, RotateTBlock)
{
    auto tBlock = blockFactory_.makeBlock(BlockShape::T, DEFAULT_SQUARE_COLOR);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*tBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*tBlock, blockRotationSimulationResult_);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*tBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*tBlock, blockRotationSimulationResult_);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*tBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*tBlock, blockRotationSimulationResult_);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*tBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*tBlock, blockRotationSimulationResult_);

    EXPECT_EQ(tBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(tBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(tBlock->getSquareCoordinates(2), Coordinates({5, 3}));
    EXPECT_EQ(tBlock->getSquareCoordinates(3), Coordinates({6, 2}));
}

TEST_F(BlockRotationTest, RotateZBlock)
{
    auto zBlock = blockFactory_.makeBlock(BlockShape::Z, DEFAULT_SQUARE_COLOR);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*zBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*zBlock, blockRotationSimulationResult_);

    blockRotationSimulationResult_ = BlockMovementManager::simulateRotation(*zBlock, placedSquares_);
    EXPECT_TRUE(blockRotationSimulationResult_.isValid());
    BlockMovementManager::applyResult(*zBlock, blockRotationSimulationResult_);

    EXPECT_EQ(zBlock->getSquareCoordinates(0), Coordinates({5, 2}));
    EXPECT_EQ(zBlock->getSquareCoordinates(1), Coordinates({4, 2}));
    EXPECT_EQ(zBlock->getSquareCoordinates(2), Coordinates({5, 3}));
    EXPECT_EQ(zBlock->getSquareCoordinates(3), Coordinates({6, 3}));
}
