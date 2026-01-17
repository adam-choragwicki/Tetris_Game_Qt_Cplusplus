#pragma once

#include <QObject>

class QmlHelper;

class OverlayManager
{
public:
    explicit OverlayManager(QmlHelper& qml_helper);

    void showEscapeMenuOverlay();
    void hideEscapeMenuOverlay();

    void showEndGameOverlay(const QString& score);
    void hideEndGameOverlay();

private:
    QmlHelper& qmlHelper_;

    QObject* const escapeMenuOverlay_;
    QObject* const endGameOverlay_;
};
