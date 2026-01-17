#include "block.h"
#include "common.h"

Block::Block(const BlockShape& blockShape, const QColor& color)
    : blockShape_(blockShape),
      color_(color),
      rotationStateToRotationCoefficientsContainerMapping(blockShapeToRotationStateToRotationCoefficientsContainerMapping.at(blockShape)),
      rotationStateIterator_(rotationStateToRotationCoefficientsContainerMapping.size())
{
    squaresCoordinates_ = BlockCoordinatesArray{
        BlockData::STARTING_CENTRAL_SQUARE_COORDINATES,
        BlockData::STARTING_CENTRAL_SQUARE_COORDINATES + rotationStateToRotationCoefficientsContainerMapping.at(rotationStateIterator_.current()).getRotationCoefficientsPair(0),
        BlockData::STARTING_CENTRAL_SQUARE_COORDINATES + rotationStateToRotationCoefficientsContainerMapping.at(rotationStateIterator_.current()).getRotationCoefficientsPair(1),
        BlockData::STARTING_CENTRAL_SQUARE_COORDINATES + rotationStateToRotationCoefficientsContainerMapping.at(rotationStateIterator_.current()).getRotationCoefficientsPair(2)
    };
}

[[nodiscard]] const BlockCoordinatesArray& Block::getAllSquaresCoordinates() const
{
    return squaresCoordinates_;
}

[[nodiscard]] const Coordinates& Block::getSquareCoordinates(const int i) const
{
    return squaresCoordinates_.at(i);
}

Coordinates Block::getCentralSquareCoordinates() const
{
    return getSquareCoordinates(0);
}

std::ostream& operator<<(std::ostream& os, const Block& block)
{
    for (const auto& coordinates: block.getAllSquaresCoordinates())
    {
        os << coordinates;
    }

    return os;
}

void Block::setBlockCoordinates(const BlockCoordinatesArray& blockCoordinatesArray)
{
    squaresCoordinates_ = blockCoordinatesArray;
    emit blockChanged();
}
