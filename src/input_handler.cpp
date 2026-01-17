#include "input_handler.h"
#include "controller.h"
#include "window_manager.h"

InputHandler::InputHandler(Controller& controller, WindowManager& windowManager)
    : QObject(&controller),
      controller_(controller),
      windowManager_(windowManager)
{
    dasTimer_.setSingleShot(true);
    dasTimer_.setInterval(dasDelayMs_);
    connect(&dasTimer_, &QTimer::timeout, this, &InputHandler::onDasTimeout);

    horizontalRepeatTimer_.setSingleShot(false);
    horizontalRepeatTimer_.setInterval(arrDelayMs_);
    connect(&horizontalRepeatTimer_, &QTimer::timeout, this, &InputHandler::onHorizontalRepeat);

    softDropTimer_.setSingleShot(false);
    softDropTimer_.setInterval(softDropRateMs_);
    connect(&softDropTimer_, &QTimer::timeout, this, &InputHandler::onSoftDropTimeout);
}

void InputHandler::keyPressed(const int key, const bool isAutoRepeat)
{
    if (isAutoRepeat) // ignore OS auto-repeat
    {
        return;
    }

    // qDebug() << "keyPressed" << key;

    switch (key)
    {
        case Qt::Key_Left:
        case Qt::Key_A:
            if (!leftKeyHeld_)
            {
                leftKeyHeld_ = true;
                rightKeyHeld_ = false;
                controller_.getStateManager().handleKeyPress(Qt::Key_Left);
                dasTimer_.start(); // when it times out, horizontalRepeatTimer_ will start
            }
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            if (!rightKeyHeld_)
            {
                rightKeyHeld_ = true;
                leftKeyHeld_ = false;
                controller_.getStateManager().handleKeyPress(Qt::Key_Right);
                dasTimer_.start();
            }
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            if (!downKeyHeld_)
            {
                downKeyHeld_ = true;
                controller_.getStateManager().handleKeyPress(Qt::Key_Down);
                softDropTimer_.start();
            }
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            controller_.getStateManager().handleKeyPress(Qt::Key_Up); // rotate, no repeat
            break;

        case Qt::Key_Space:
            controller_.getStateManager().handleKeyPress(Qt::Key_Space); // hard drop
            break;

        case Qt::Key_F11:
            windowManager_.toggleFullScreen();
            break;

        case Qt::Key_Escape:
            controller_.getStateManager().handleKeyPress(Qt::Key_Escape);
            break;

        default:
            break;
    }
}

void InputHandler::keyReleased(const int key, const bool isAutoRepeat)
{
    if (isAutoRepeat) // ignore OS auto-repeat
    {
        return;
    }

    // qDebug() << "keyReleased" << key;

    switch (key)
    {
        case Qt::Key_Left:
        case Qt::Key_A:
            leftKeyHeld_ = false;
            dasTimer_.stop();
            horizontalRepeatTimer_.stop();
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            rightKeyHeld_ = false;
            dasTimer_.stop();
            horizontalRepeatTimer_.stop();
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            downKeyHeld_ = false;
            softDropTimer_.stop();
            break;

        default:
            break;
    }
}

void InputHandler::onDasTimeout()
{
    // DAS expired — start horizontal repeats
    horizontalRepeatTimer_.start();
}

void InputHandler::onHorizontalRepeat()
{
    if (leftKeyHeld_)
    {
        controller_.getStateManager().handleKeyPress(Qt::Key_Left);
    }
    else if (rightKeyHeld_)
    {
        controller_.getStateManager().handleKeyPress(Qt::Key_Right);
    }
    else
    {
        horizontalRepeatTimer_.stop();
    }
}

void InputHandler::onSoftDropTimeout()
{
    controller_.getStateManager().handleKeyPress(Qt::Key_Down);
}
