#include "active_block_manager.h"
#include <QDebug>

void ActiveBlockManager::createBlock()
{
    if (activeBlock_)
    {
        qFatal("Error, trying to create a block when one already exists");
    }

    activeBlock_ = blockFactory_.makeRandomBlock();

    qInfo().nospace() << "Created block #" << ++blockCounter_;

    connect(activeBlock_.get(), &Block::blockChanged, this, &ActiveBlockManager::activeBlockChanged);

    emit activeBlockChanged();
}

void ActiveBlockManager::destroyBlock()
{
    Q_ASSERT(activeBlock_);

    activeBlock_.reset();
    emit activeBlockDestroyed();
}

bool ActiveBlockManager::blockExists() const
{
    return activeBlock_ != nullptr;
}

const Block& ActiveBlockManager::getActiveBlock() const
{
    return *activeBlock_;
}

Block& ActiveBlockManager::getActiveBlock()
{
    return *activeBlock_;
}
