#include "model/active_block_model.h"
#include "model.h"
#include "block.h"
#include "coordinates.h"

ActiveBlockModel::ActiveBlockModel(ActiveBlockManager& activeBlockManager) : activeBlockManager_(activeBlockManager)
{
    connect(&activeBlockManager_, &ActiveBlockManager::activeBlockChanged, this, &ActiveBlockModel::refresh);
}

void ActiveBlockModel::refresh()
{
    squares_.clear();

    if (!activeBlockManager_.blockExists())
    {
        blockColor_ = QColor();
        emit activeBlockChanged();
        return;
    }

    const Block& block = activeBlockManager_.getActiveBlock();
    blockColor_ = block.getColor();

    for (const auto& [x, y]: block.getAllSquaresCoordinates())
    {
        QVariantMap variantMap;
        variantMap.insert("x", x);
        variantMap.insert("y", y);
        squares_.append(variantMap);
    }

    emit activeBlockChanged();
}
