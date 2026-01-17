#pragma once

#include "active_block_model.h"
#include "score_manager.h"
#include "active_block_manager.h"
#include "placed_squares.h"
#include "placed_squares_model.h"

class GameConfig;

class Model : public QObject
{
    Q_OBJECT

signals:
    void scoreChanged(int);

public:
    explicit Model();
    void reset();

    [[nodiscard]] const ScoreManager& getScoreManager() const { return scoreManager_; }
    [[nodiscard]] ScoreManager& getScoreManager() { return scoreManager_; }

    [[nodiscard]] const ActiveBlockManager& getActiveBlockManager() const { return activeBlockManager_; }
    [[nodiscard]] ActiveBlockManager& getActiveBlockManager() { return activeBlockManager_; }

    [[nodiscard]] const PlacedSquares& getPlacedSquares() const { return *placedSquares_; }
    [[nodiscard]] PlacedSquares& getPlacedSquares() { return *placedSquares_; }

    [[nodiscard]] ActiveBlockModel& getActiveBlockModel() const { return *activeBlockModel_; }

    [[nodiscard]] PlacedSquaresModel& getPlacedSquaresModel() const { return *placedSquaresModel_; }

    void updatePlacedSquaresModel();

private:
    std::unique_ptr<PlacedSquares> placedSquares_;
    std::unique_ptr<PlacedSquaresModel> placedSquaresModel_;

    ScoreManager scoreManager_;

    ActiveBlockManager activeBlockManager_;

    std::unique_ptr<ActiveBlockModel> activeBlockModel_;
};
