#pragma once

#include <QAbstractListModel>
#include <vector>
#include <QColor>

class PlacedSquares;

struct PlacedSquareItem
{
    int x;
    int y;
    QColor color;
};

class PlacedSquaresModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles
    {
        XRole = Qt::UserRole + 1,
        YRole,
        ColorRole
    };

    explicit PlacedSquaresModel(PlacedSquares& placedSquares, QObject* parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void refresh(); // rebuild internal cache and notify views

private:
    void rebuildCache();

    PlacedSquares& placedSquares_;
    std::vector<PlacedSquareItem> cache_;
};
