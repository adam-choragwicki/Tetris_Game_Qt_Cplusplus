#include "placed_squares_model.h"
#include "placed_squares.h"
#include "coordinates.h"
#include "square.h"

PlacedSquaresModel::PlacedSquaresModel(PlacedSquares& placedSquares, QObject* parent) : QAbstractListModel(parent), placedSquares_(placedSquares)
{
    // initial cache population
    rebuildCache();

    // refresh when underlying data changes
    connect(&placedSquares_, &PlacedSquares::changed, this, &PlacedSquaresModel::refresh);
}

int PlacedSquaresModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return static_cast<int>(cache_.size());
}

QVariant PlacedSquaresModel::data(const QModelIndex& index, const int role) const
{
    if (!index.isValid())
    {
        Q_ASSERT(false);
        return {};
    }

    const int row = index.row();

    if (row < 0 || row >= static_cast<int>(cache_.size()))
    {
        Q_ASSERT(false);
        return {};
    }

    const auto& [x, y, color] = cache_.at(row);

    switch (role)
    {
        case XRole: return x;
        case YRole: return y;
        case ColorRole: return color; // QVariant can carry QColor
        default: return {};
    }
}

QHash<int, QByteArray> PlacedSquaresModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[XRole] = "x";
    roles[YRole] = "y";
    roles[ColorRole] = "color";
    return roles;
}

void PlacedSquaresModel::refresh()
{
    beginResetModel();
    rebuildCache();
    endResetModel();
}

void PlacedSquaresModel::rebuildCache()
{
    cache_.clear();
    cache_.reserve(placedSquares_.size());

    for (const auto& [coordinates, square]: placedSquares_)
    {
        const QColor color = square.getColor();
        cache_.push_back({coordinates.x, coordinates.y, color});
    }
}
