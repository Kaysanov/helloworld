#ifndef MOUSEEVENTPROCESSOR_H
#define MOUSEEVENTPROCESSOR_H

#include <SDL3/SDL.h>
#include <functional>
#include <unordered_map>

class MouseEventProcessor {
public:
    using PositionCallback = std::function<void(int, int)>;
    using WheelCallback = std::function<void(float, float)>;
    using ClickCallback = std::function<void()>;
    
    void register_motion_callback(PositionCallback callback);
    void register_wheel_callback(WheelCallback callback);
    void register_click_callback(Uint8 button, ClickCallback callback);
    void process_event(const SDL_Event* event);

private:
    PositionCallback motion_callback = nullptr;
    WheelCallback wheel_callback = nullptr;
    std::unordered_map<Uint8, ClickCallback> click_callbacks;
};

#endif