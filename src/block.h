#pragma once

#include "random_generator.h"
#include "common.h"
#include "rotation_coefficients_database.h"
#include <QObject>

class Block : public QObject
{
    Q_OBJECT

    friend std::ostream& operator<<(std::ostream& os, const Block& block);

signals:
    void blockChanged();

public:
    explicit Block(const BlockShape& blockShape, const QColor& color);

    [[nodiscard]] const BlockCoordinatesArray& getAllSquaresCoordinates() const;

    [[nodiscard]] const Coordinates& getSquareCoordinates(int i) const;

    [[nodiscard]] Coordinates getCentralSquareCoordinates() const;

    [[nodiscard]] const QColor& getColor() const { return color_; }

    [[nodiscard]] const RotationStateToRotationCoefficientsContainerMapping& getRotationCoefficients() const { return rotationStateToRotationCoefficientsContainerMapping; }

    [[nodiscard]] const RotationStateIterator& getRotationStateIterator() const { return rotationStateIterator_; }

    [[nodiscard]] RotationStateIterator& getRotationStateIterator() { return rotationStateIterator_; }

    void setBlockCoordinates(const BlockCoordinatesArray& blockCoordinatesArray);

private:
    const BlockShape blockShape_;
    const QColor color_;
    const RotationStateToRotationCoefficientsContainerMapping& rotationStateToRotationCoefficientsContainerMapping;

    RotationStateIterator rotationStateIterator_;
    BlockCoordinatesArray squaresCoordinates_{};
};
