#pragma once

#include <QColor>

class Square
{
public:
    explicit Square(const QColor& color) : color_(color)
    {}

    [[nodiscard]] const QColor& getColor() const { return color_; }

private:
    const QColor color_;
};
