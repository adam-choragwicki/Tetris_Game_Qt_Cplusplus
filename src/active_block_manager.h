#pragma once

#include "block_factory.h"
#include <QObject>

class ActiveBlockManager : public QObject
{
    Q_OBJECT

signals:
    void activeBlockChanged();
    void activeBlockDestroyed();

public:
    void createBlock();
    void destroyBlock();
    [[nodiscard]] bool blockExists() const;
    [[nodiscard]] const Block& getActiveBlock() const;
    [[nodiscard]] Block& getActiveBlock();

private:
    inline static int blockCounter_{};

    BlockFactory blockFactory_;
    std::unique_ptr<Block> activeBlock_;
};
