#include "score_manager.h"
#include <stdexcept>
#include <QDebug>

void ScoreManager::addRewardForFullRowsToScoreBalance(const unsigned int fullRowsCount)
{
    switch (fullRowsCount)
    {
        case 1:
            increaseScore(1);
            break;
        case 2:
            increaseScore(3);
            break;
        case 3:
            increaseScore(7);
            break;
        case 4:
            increaseScore(10);
            break;
        default:
            throw std::runtime_error("Wrong full rows count");
    }
}

void ScoreManager::reset()
{
    score_ = 0;
    emit scoreChanged(score_);
}

void ScoreManager::increaseScore(const int score)
{
    qInfo() << "Score increased by" << score;

    score_ += score;
    emit scoreChanged(score_);
}
