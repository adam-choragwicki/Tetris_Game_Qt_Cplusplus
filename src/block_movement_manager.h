#pragma once

#include "block.h"
#include "placed_squares.h"
#include "simulation_result.h"
#include "direction.h"

class BlockMovementManager
{
public:
    static SimulationResult simulateMove(const Block& block, Direction direction, const PlacedSquares& squares);
    static SimulationResult simulateRotation(const Block& block, const PlacedSquares& squares);

    static SimulationResult simulateHardDrop(const Block& block, const PlacedSquares& squares); // Hard drop: returns the result for the final bottom-most position

    static void applyResult(Block& block, const SimulationResult& result); // Single point of entry for state modification

    static bool canMove(const Block& block, Direction direction, const PlacedSquares& squares);

    static bool validateBlock(const BlockCoordinatesArray& blockCoordinates, const PlacedSquares& squares);

private:
    static std::pair<int, int> getOffset(Direction direction);
};
