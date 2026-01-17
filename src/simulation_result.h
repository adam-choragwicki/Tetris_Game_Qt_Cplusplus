#pragma once

#include "coordinates.h"

class SimulationResult
{
public:
    enum class Type { Movement, Rotation };

    SimulationResult() = default; // default constructor for invalid results

    // Successful simulation
    SimulationResult(const Type type, const BlockCoordinatesArray& blockCoordinates) : type_(type), coordinates_(blockCoordinates), isValid_(true) {}

    [[nodiscard]] bool isValid() const { return isValid_; }
    [[nodiscard]] Type getType() const { return type_; }
    [[nodiscard]] const BlockCoordinatesArray& getCoordinates() const { return coordinates_; }

private:
    Type type_ = Type::Movement;
    BlockCoordinatesArray coordinates_{};
    bool isValid_ = false;
};
