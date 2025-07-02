#ifndef EVENTPROCESSOR_H
#define EVENTPROCESSOR_H

#include <SDL3/SDL.h>
#include <functional>

class InputState;
class HotkeyRegistry;

class EventProcessor
{
public:
    using MousePositionCallback = std::function<void(int, int)>;
    using MouseWheelCallback = std::function<void(float, float)>;

    void setMouseMoveCallback(MousePositionCallback callback);
    void setMouseWheelCallback(MouseWheelCallback callback);

    void processEvent(const SDL_Event *event, InputState &inputState, HotkeyRegistry &registry);

private:
    MousePositionCallback mouseMoveCallback = nullptr;
    MouseWheelCallback mouseWheelCallback = nullptr;
};

#endif // EVENTPROCESSOR_H