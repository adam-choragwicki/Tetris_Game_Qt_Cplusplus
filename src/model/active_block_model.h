#pragma once

#include <QVariantList>
#include <QColor>

class ActiveBlockManager;

/// QML adapter for ActiveBlockManager
class ActiveBlockModel : public QObject
{
    Q_OBJECT

signals:
    void activeBlockChanged();

public:
    explicit ActiveBlockModel(ActiveBlockManager& activeBlockManager);

    Q_PROPERTY(QVariantList squares READ getSquares NOTIFY activeBlockChanged)
    [[nodiscard]] QVariantList getSquares() const { return squares_; }

    Q_PROPERTY(QColor color READ getColor NOTIFY activeBlockChanged)
    [[nodiscard]] QColor getColor() const { return blockColor_; }

private slots:
    void refresh();

private:
    ActiveBlockManager& activeBlockManager_;
    QVariantList squares_;
    QColor blockColor_;
};
