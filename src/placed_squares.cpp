#include "placed_squares.h"
#include "block.h"
#include <stdexcept>
#include <QDebug>

PlacedSquares::PlacedSquares(QObject* parent) : QObject(parent)
{
    // 1 square
    // addSquare({1, 1}, QColor(Qt::red));

    // 1 row
    // for (int x = 1; x <= 10; ++x)
    // {
    //     if (x == 5)
    //     {
    //         continue;
    //     }
    //     addSquare({x, 20}, QColor(Qt::red));
    // }

    // 4 rows
    // for (int y = 17; y <= 20; ++y)
    // {
    //     for (int x = 1; x <= 10; ++x)
    //     {
    //         if (x == 5)
    //         {
    //             continue;
    //         }
    //         addSquare({x, y}, QColor(Qt::red));
    //     }
    // }

    // 8 rows
    // for (int y = 13; y <= 20; ++y)
    // {
    //     for (int x = 1; x <= 10; ++x)
    //     {
    //         if (x == 5)
    //         {
    //             continue;
    //         }
    //         addSquare({x, y}, QColor(Qt::red));
    //     }
    // }

    // 12 rows
    // for (int y = 9; y <= 20; ++y)
    // {
    //     for (int x = 1; x <= 10; ++x)
    //     {
    //         if (x == 5)
    //         {
    //             continue;
    //         }
    //         addSquare({x, y}, QColor(Qt::red));
    //     }
    // }

    // 16 rows
    // for (int y = 5; y <= 20; ++y)
    // {
    //     for (int x = 1; x <= 10; ++x)
    //     {
    //         if (x == 5)
    //         {
    //             continue;
    //         }
    //         addSquare({x, y}, QColor(Qt::red));
    //     }
    // }
}

void PlacedSquares::reset()
{
    coordinatesToSquaresMapping_.clear();
    emit changed();
}

/**
 * Adds square to mapping. Emits changed signal if it is an independent operation. Otherwise, if it is part of another operation the caller should take care of emitting the signal.
 *
 * @param squareCoordinates Coordinates of the square to be added.
 * @param color Color of the square to be added.
 * @param isIndependentOperation If function is called as an independent operation.
 */
void PlacedSquares::addSquare(const Coordinates& squareCoordinates, const QColor& color, const bool isIndependentOperation)
{
    const auto& [_, inserted] = coordinatesToSquaresMapping_.emplace(squareCoordinates, color);

    if (!inserted)
    {
        throw std::runtime_error("Error, placing square on non-empty field");
    }

    if (isIndependentOperation)
    {
        emit changed();
    }
}

/**
 * Removes square from mapping. Emits changed signal if it is an independent operation. Otherwise, if it is part of another operation the caller should take care of emitting the signal.
 *
 * @param squareCoordinates Coordinates of the square to be removed.
 * @param isIndependentOperation If function is called as an independent operation.
 */
void PlacedSquares::removeSquare(const Coordinates& squareCoordinates, const bool isIndependentOperation)
{
    const size_t removed = coordinatesToSquaresMapping_.erase(squareCoordinates);

    if (removed == 0)
    {
        throw std::runtime_error("Error, trying to remove square from already empty field");
    }

    if (isIndependentOperation)
    {
        emit changed();
    }
}

void PlacedSquares::removeRow(const int rowNumber, const bool isIndependentOperation)
{
    qInfo() << "Removing row" << rowNumber;

    if (rowNumber >= Arena::MINIMUM_Y && rowNumber <= Arena::MAXIMUM_Y)
    {
        for (int x = Arena::MINIMUM_X; x <= Arena::MAXIMUM_X; ++x)
        {
            removeSquare(Coordinates{x, rowNumber}, false);
        }
    }
    else
    {
        throw std::runtime_error("Error, wrong row number given during row removal");
    }

    if (isIndependentOperation)
    {
        emit changed();
    }
}

std::vector<int> PlacedSquares::findFullRowsNumbers() const
{
    std::vector<int> fullRowsNumbers;

    /*Go through all rows*/
    for (int row = Arena::MINIMUM_Y; row <= Arena::MAXIMUM_Y; ++row)
    {
        for (int column = Arena::MINIMUM_X; column <= Arena::MAXIMUM_X; ++column)
        {
            if (!isTileAtCoordinatesOccupied(Coordinates{column, row}))
            {
                break;
            }

            if (column == Arena::MAXIMUM_X)
            {
                fullRowsNumbers.push_back(row);
            }
        }
    }

    if (fullRowsNumbers.size() > 4)
    {
        throw std::runtime_error("Error, wrong full rows count: " + std::to_string(fullRowsNumbers.size()));
    }

    return fullRowsNumbers;
}

void PlacedSquares::dropRowsAboveGivenRow(const int removedRow, const bool isIndependentOperation)
{
    qInfo() << "Dropping rows above row" << removedRow;

    /*Go through all columns*/
    for (int x = Arena::MINIMUM_X; x <= Arena::MAXIMUM_X; ++x)
    {
        /*Go through rows above given row*/
        for (int y = removedRow - 1; y > Arena::MINIMUM_Y; --y)
        {
            const Coordinates coordinates{x, y};

            if (isTileAtCoordinatesOccupied(coordinates))
            {
                const Coordinates coordinatesOneRowBelow{x, y + 1};

                if (!isTileAtCoordinatesOccupied(coordinatesOneRowBelow))
                {
                    auto nodeHandle = coordinatesToSquaresMapping_.extract(coordinates);
                    nodeHandle.key() = coordinatesOneRowBelow;
                    coordinatesToSquaresMapping_.insert(std::move(nodeHandle));
                }
                else
                {
                    throw std::runtime_error("Error, cannot drop rows above given row. Square one row below is not empty.");
                }
            }
        }
    }

    if (isIndependentOperation)
    {
        emit changed();
    }
}

void PlacedSquares::placeBlock(const Block& block)
{
    for (const auto& squareCoordinates: block.getAllSquaresCoordinates())
    {
        addSquare(squareCoordinates, block.getColor(), false);
    }

    emit changed();
}
