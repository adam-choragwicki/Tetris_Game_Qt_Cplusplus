#pragma once

#include "square.h"
#include "coordinates.h"
#include <map>
#include <vector>
#include <QObject>

class Block;

class PlacedSquares : public QObject
{
    Q_OBJECT

    using CoordinatesToSquaresMapping = std::map<Coordinates, Square>;

signals:
    void changed();

public:
    explicit PlacedSquares(QObject* parent = nullptr);
    void reset();

    // Modifying operations
    void placeBlock(const Block& block);

    void addSquare(const Coordinates& squareCoordinates, const QColor& color, bool isIndependentOperation = true);
    void removeRow(int rowNumber, bool isIndependentOperation = true);
    void dropRowsAboveGivenRow(int removedRow, bool isIndependentOperation = true);

    // Non-modifying operations
    [[nodiscard]] std::vector<int> findFullRowsNumbers() const;

    [[nodiscard]] bool isTileAtCoordinatesOccupied(const Coordinates& coordinates) const { return coordinatesToSquaresMapping_.contains(coordinates); }

    size_t size() const { return coordinatesToSquaresMapping_.size(); }

    [[nodiscard]] CoordinatesToSquaresMapping::const_iterator begin() const { return coordinatesToSquaresMapping_.cbegin(); }
    [[nodiscard]] CoordinatesToSquaresMapping::const_iterator end() const { return coordinatesToSquaresMapping_.cend(); }

private:
    void removeSquare(const Coordinates& squareCoordinates, bool isIndependentOperation = true);

    CoordinatesToSquaresMapping coordinatesToSquaresMapping_;
};
