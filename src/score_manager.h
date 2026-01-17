#pragma once

#include <QObject>

class ScoreManager : public QObject
{
    Q_OBJECT

signals:
    void scoreChanged(int);

public:
    void addRewardForFullRowsToScoreBalance(unsigned int fullRowsCount);
    void reset();

    Q_PROPERTY(int score READ getScore NOTIFY scoreChanged)
    [[nodiscard]] int getScore() const { return score_; }

private:
    int score_{};

    void increaseScore(int score);
};
