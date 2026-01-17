#pragma once

#include <cstddef>

class RotationState
{
public:
    explicit RotationState(int state);

    void increment() { ++state_; }

    void setState(const int state) { state_ = state; }

    [[nodiscard]] int toInt() const { return state_; }

    bool operator<(const RotationState& other) const { return state_ < other.state_; }

private:
    int state_;
};

class RotationStateIterator
{
public:
    explicit RotationStateIterator(const size_t rotationStatesCount) : rotationStatesCount_(rotationStatesCount), rotationState_(0)
    {}

    void advance();

    [[nodiscard]] RotationState current() const;

    [[nodiscard]] RotationState peekNext() const;

private:
    const size_t rotationStatesCount_;
    RotationState rotationState_;
};
