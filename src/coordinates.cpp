#include "coordinates.h"
#include "common.h"

bool Coordinates::validateCoordinates(const Coordinates& coordinates)
{
    return coordinates.x >= Arena::MINIMUM_X && coordinates.x <= Arena::MAXIMUM_X && coordinates.y >= Arena::MINIMUM_Y && coordinates.y <= Arena::MAXIMUM_Y;
}

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return (coordinates1.x == coordinates2.x) && (coordinates1.y == coordinates2.y);
}

bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return !(coordinates1 == coordinates2);
}

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    if (coordinates1.x < coordinates2.x)
    {
        return true;
    }

    if (coordinates1.x > coordinates2.x)
    {
        return false;
    }

    return coordinates1.y < coordinates2.y;
}

Coordinates Coordinates::operator+(const RotationCoefficients& rotationCoefficients) const
{
    return Coordinates{x + rotationCoefficients.getRotationCoefficients().first, y + rotationCoefficients.getRotationCoefficients().second};
}

void Coordinates::operator+=(const Coordinates& coordinates)
{
    x += coordinates.x;
    y += coordinates.y;
}

Coordinates Coordinates::operator-(const Coordinates& coordinates) const
{
    return {x - coordinates.x, y - coordinates.y};
}

Coordinates Coordinates::operator+(const std::pair<int, int>& coefficientsPair) const
{
    return {x + coefficientsPair.first, y + coefficientsPair.second};
}

std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates)
{
    os << "[" << coordinates.x << "," << coordinates.y << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Coordinates>& coordinatesVector)
{
    for (const auto& [x, y]: coordinatesVector)
    {
        os << "[" << x << "," << y << "]";
    }

    return os;
}
