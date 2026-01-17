#pragma once

#include <QTimer>

class Controller;
class WindowManager;

class InputHandler : public QObject
{
    Q_OBJECT

public:
    explicit InputHandler(Controller& controller, WindowManager& windowManager);

    Q_INVOKABLE void keyPressed(int key, bool isAutoRepeat);
    Q_INVOKABLE void keyReleased(int key, bool isAutoRepeat);

private slots:
    void onDasTimeout();
    void onHorizontalRepeat();
    void onSoftDropTimeout();

private:
    Controller& controller_;
    WindowManager& windowManager_;

    bool leftKeyHeld_ = false;
    bool rightKeyHeld_ = false;
    bool downKeyHeld_ = false;

    QTimer dasTimer_; // DAS = Delayed Auto Shift
    QTimer horizontalRepeatTimer_;
    QTimer softDropTimer_;

    int dasDelayMs_ = 120;
    int arrDelayMs_ = 40; // ARR = Auto Repeat Rate
    int softDropRateMs_ = 30;
};
