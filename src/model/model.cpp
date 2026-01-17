#include "model.h"

Model::Model()
{
    placedSquares_ = std::make_unique<PlacedSquares>();
    placedSquaresModel_ = std::make_unique<PlacedSquaresModel>(*placedSquares_);

    activeBlockModel_ = std::make_unique<ActiveBlockModel>(activeBlockManager_);

    connect(&scoreManager_, &ScoreManager::scoreChanged, this, &Model::scoreChanged);
}

void Model::reset()
{
    scoreManager_.reset();

    placedSquares_->reset();
}

void Model::updatePlacedSquaresModel()
{
    placedSquaresModel_->refresh();
}
