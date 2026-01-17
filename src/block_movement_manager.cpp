#include "block_movement_manager.h"

std::pair<int, int> BlockMovementManager::getOffset(const Direction direction)
{
    switch (direction)
    {
        case Direction::LEFT: return {-1, 0};
        case Direction::RIGHT: return {1, 0};
        case Direction::DOWN: return {0, 1};
        default: return {0, 0};
    }
}

bool BlockMovementManager::validateBlock(const BlockCoordinatesArray& blockCoordinates, const PlacedSquares& squares)
{
    for (const auto& coordinates: blockCoordinates)
    {
        // Check Arena boundaries
        if (!Coordinates::validateCoordinates(coordinates))
        {
            return false;
        }

        // Check collisions with the existing placed squares
        if (squares.isTileAtCoordinatesOccupied(coordinates))
        {
            return false;
        }
    }

    return true;
}

SimulationResult BlockMovementManager::simulateMove(const Block& block, Direction direction, const PlacedSquares& squares)
{
    auto [dx, dy] = getOffset(direction);

    BlockCoordinatesArray newBlockCoordinates;

    for (int i = 0; i < 4; ++i)
    {
        newBlockCoordinates[i] = block.getSquareCoordinates(i) + std::pair{dx, dy};
    }

    if (!validateBlock(newBlockCoordinates, squares))
    {
        return {};
    }

    return {SimulationResult::Type::Movement, newBlockCoordinates};
}

SimulationResult BlockMovementManager::simulateRotation(const Block& block, const PlacedSquares& squares)
{
    const auto& rotationStateCoefficientsMapping = block.getRotationCoefficients();
    const auto nextState = block.getRotationStateIterator().peekNext();
    const Coordinates centralSquarePivot = block.getCentralSquareCoordinates();

    BlockCoordinatesArray newBlockCoordinates;
    newBlockCoordinates[0] = centralSquarePivot; // Central square stays or moves relative to pivot

    for (int i = 1; i < 4; ++i)
    {
        newBlockCoordinates[i] = centralSquarePivot + rotationStateCoefficientsMapping.at(nextState).getRotationCoefficientsPair(i - 1);
    }

    if (!validateBlock(newBlockCoordinates, squares))
    {
        return {};
    }

    return {SimulationResult::Type::Rotation, newBlockCoordinates};
}

void BlockMovementManager::applyResult(Block& block, const SimulationResult& result)
{
    if (!result.isValid())
    {
        return;
    }

    block.setBlockCoordinates(result.getCoordinates());

    // If it was a rotation, we must also advance the internal state
    if (result.getType() == SimulationResult::Type::Rotation)
    {
        block.getRotationStateIterator().advance();
    }
}

bool BlockMovementManager::canMove(const Block& block, const Direction direction, const PlacedSquares& squares)
{
    return simulateMove(block, direction, squares).isValid();
}

SimulationResult BlockMovementManager::simulateHardDrop(const Block& block, const PlacedSquares& squares)
{
    BlockCoordinatesArray currentCoordinates = block.getAllSquaresCoordinates();
    BlockCoordinatesArray lastValidCoordinates = currentCoordinates;

    while (true)
    {
        BlockCoordinatesArray nextCoordinates;

        for (size_t i = 0; i < 4; ++i)
        {
            nextCoordinates[i] = {currentCoordinates[i].x, currentCoordinates[i].y + 1};
        }

        if (!validateBlock(nextCoordinates, squares))
        {
            break;
        }

        lastValidCoordinates = nextCoordinates;
        currentCoordinates = nextCoordinates;
    }

    return {SimulationResult::Type::Movement, lastValidCoordinates};
}
